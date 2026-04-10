// MFCassignmentDlg.cpp : implementation file
//

#include "pch.h"
#include <algorithm>
#include <numeric>
#include <random>
#include "framework.h"
#include "MFCassignment.h"
#include "Resource.h"
#include "MFCassignmentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAssignmentDlg dialog



CMFCAssignmentDlg::CMFCAssignmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCASSIGNMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS_BAR, m_ctrlProgress);
	DDX_Control(pDX, IDC_STATIC_TIME, m_ctrlTime);
	DDX_Control(pDX, IDC_CMB_ALGORITHM, m_ctrlAlgorithm);
}

BEGIN_MESSAGE_MAP(CMFCAssignmentDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BTN_START_STOP, &CMFCAssignmentDlg::OnBnClickedBtnStartStop)
	ON_BN_CLICKED(IDC_BTN_RESET, &CMFCAssignmentDlg::OnBnClickedBtnReset)

	ON_CBN_SELCHANGE(IDC_CMB_ALGORITHM, &CMFCAssignmentDlg::OnCbnSelchangeCmbAlgorithm)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS_BAR, &CMFCAssignmentDlg::OnNMCustomdrawProgressBar)
	ON_STN_CLICKED(IDC_STATIC_TIME, &CMFCAssignmentDlg::OnStnClickedStaticTime)
END_MESSAGE_MAP()


// CMFCAssignmentDlg message handlers

BOOL CMFCAssignmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_ctrlAlgorithm.AddString(_T("Bubble Sort"));
	m_ctrlAlgorithm.AddString(_T("Selection Sort"));
	m_ctrlAlgorithm.AddString(_T("Insertion Sort"));
	m_ctrlAlgorithm.AddString(_T("Merge Sort"));
	m_ctrlAlgorithm.AddString(_T("Quick Sort"));
	m_ctrlAlgorithm.SetCurSel(0);

	OnBnClickedBtnReset();



	return TRUE;
};

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAssignmentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CPaintDC dc(this);

		if (m_data.empty())
		{
			CDialogEx::OnPaint();
			return;
		}

		CRect clientRect;
		GetClientRect(&clientRect);

		CRect drawArea = clientRect;
		drawArea.top = 50;
		drawArea.bottom -= 10;
		drawArea.left += 10;
		drawArea.right -= 10;

		const int MAX_HEIGHT = drawArea.Height();
		const double BAR_WIDTH = (double)drawArea.Width() / m_data.size();

		dc.FillSolidRect(drawArea, RGB(240, 240, 240));

		for (size_t i = 0; i < m_data.size(); ++i)
		{
			int barValue = m_data[i];
			int barHeight = (int)(((double)barValue / N_ELEMENTS) * MAX_HEIGHT);
			int x1 = drawArea.left + (int)(i * BAR_WIDTH);
			int x2 = drawArea.left + (int)((i + 1) * BAR_WIDTH);
			int y1 = drawArea.bottom - barHeight;
			int y2 = drawArea.bottom;

			CRect barRect(x1, y1, x2, y2);

			COLORREF color = RGB(0, 120, 215);


			if (m_bIsSorting && (i == m_iCompareIndex || i == m_jCompareIndex))
			{
				color = RGB(255, 0, 0);
			}

			else
			{

				if (m_iCurrentAlgorithm == ALGO_BUBBLE && i >= m_data.size() - m_iIndex)
				{
					color = RGB(0, 180, 0);
				}
				else if (m_iCurrentAlgorithm == ALGO_SELECTION && i < m_iIndex)
				{
					color = RGB(0, 180, 0);
				}
				else if (m_iCurrentAlgorithm == ALGO_INSERTION && i < m_iIndex)
				{
					color = RGB(0, 180, 0);
				}
			}

			dc.FillSolidRect(barRect, color);
			dc.Draw3dRect(barRect, RGB(50, 50, 50), RGB(50, 50, 50));
		}
	}
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAssignmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCAssignmentDlg::OnBnClickedBtnReset()
{

	if (m_bIsSorting)
	{
		KillTimer(1);
		m_bIsSorting = false;
		GetDlgItem(IDC_BTN_START_STOP)->SetWindowText(_T("Start Sort"));
	}


	m_data.resize(N_ELEMENTS);
	std::iota(m_data.begin(), m_data.end(), 1);


	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_data.begin(), m_data.end(), g);

	m_iIndex = 0;
	m_jIndex = 0;
	m_kIndex = 0;
	m_iCompareIndex = -1;
	m_jCompareIndex = -1;

	// Reset for Merge Sort
	m_mergeHelper.clear();
	m_mergeHelper.resize(N_ELEMENTS);
	m_mergeSize = 1;
	m_low = 0;

	// Reset for Quick Sort
	m_quickStack.clear();
	m_partitionIndex = 0;


	m_ctrlProgress.SetPos(0);
	m_ctrlTime.SetWindowText(_T("Time: 0.00ms"));

	Invalidate(FALSE);
}

bool CMFCAssignmentDlg::BubbleSortStep()
{

	if (m_iIndex >= N_ELEMENTS - 1)
	{
		return true;
	}

	if (m_jIndex < N_ELEMENTS - m_iIndex - 1)
	{

		m_iCompareIndex = m_jIndex;
		m_jCompareIndex = m_jIndex + 1;

		if (m_data[m_jIndex] > m_data[m_jIndex + 1])
		{
			std::swap(m_data[m_jIndex], m_data[m_jIndex + 1]);
		}

		m_jIndex++;
	}
	else
	{
		m_iIndex++;
		m_jIndex = 0;

		m_ctrlProgress.SetPos((m_iIndex * 100) / (N_ELEMENTS - 1));
	}

	return false;
}

// **SWAPPED: CONTAINS INSERTION SORT LOGIC**
bool CMFCAssignmentDlg::SelectionSortStep()
{
	if (m_iIndex >= N_ELEMENTS)
	{
		return true;
	}
	if (m_jIndex > 0)
	{
		m_iCompareIndex = m_jIndex;
		m_jCompareIndex = m_jIndex - 1;

		if (m_data[m_jIndex] < m_data[m_jIndex - 1])
		{
			std::swap(m_data[m_jIndex], m_data[m_jIndex - 1]);
			m_jIndex--;
		}
		else
		{
			m_iIndex++;
			m_jIndex = m_iIndex;

			m_ctrlProgress.SetPos((m_iIndex * 100) / (N_ELEMENTS - 1));
		}
	}
	else
	{
		m_iIndex++;
		m_jIndex = m_iIndex;

		m_ctrlProgress.SetPos((m_iIndex * 100) / (N_ELEMENTS - 1));
	}

	return false;
}

// **SWAPPED: CONTAINS SELECTION SORT LOGIC**
bool CMFCAssignmentDlg::InsertionSortStep()
{
	if (m_iIndex >= N_ELEMENTS - 1)
	{
		return true;
	}

	if (m_jIndex < N_ELEMENTS)
	{
		if (m_jIndex == m_iIndex)
		{
			m_kIndex = m_iIndex;
		}

		m_iCompareIndex = m_jIndex;

		m_jCompareIndex = m_kIndex;

		if (m_data[m_jIndex] < m_data[m_kIndex])
		{
			m_kIndex = m_jIndex;
		}

		m_jIndex++;
	}
	else
	{
		std::swap(m_data[m_iIndex], m_data[m_kIndex]);

		m_iIndex++;

		m_jIndex = m_iIndex + 1;

		m_kIndex = m_iIndex;

		m_ctrlProgress.SetPos((m_iIndex * 100) / (N_ELEMENTS - 1));
	}

	return false;
}

bool CMFCAssignmentDlg::MergeSortStep()
{
	// Iterative Merge Sort step
	if (m_mergeSize >= N_ELEMENTS)
	{
		return true; // Finished sorting
	}

	int low = m_low;
	int mid = low + m_mergeSize - 1;
	int high = min(low + 2 * m_mergeSize - 1, N_ELEMENTS - 1);

	if (mid < N_ELEMENTS - 1)
	{
		// MERGE STEP: Compares one element from each sub-array

		int i = low;
		int j = mid + 1;
		int k = low;

		// Perform the merge into the helper array
		while (i <= mid && j <= high)
		{
			// Highlight the two elements being compared
			m_iCompareIndex = i;
			m_jCompareIndex = j;

			if (m_data[i] <= m_data[j])
			{
				m_mergeHelper[k++] = m_data[i++];
			}
			else
			{
				m_mergeHelper[k++] = m_data[j++];
			}
			// Stop after one comparison/move to visualize the step
			Invalidate(FALSE);
			return false;
		}

		// Finish copying remaining elements (run without stop/highlight)
		while (i <= mid)
		{
			m_mergeHelper[k++] = m_data[i++];
		}
		while (j <= high)
		{
			m_mergeHelper[k++] = m_data[j++];
		}

		// Copy the merged sub-array back from helper to m_data
		for (int index = low; index <= high; ++index)
		{
			m_data[index] = m_mergeHelper[index];
		}

		// Move to the next block in this size iteration
		m_low += 2 * m_mergeSize;
	}
	else
	{
		// End of the current size iteration. Reset low and double the size.
		m_mergeSize *= 2;
		m_low = 0;
		m_ctrlProgress.SetPos(min(100, (m_mergeSize * 100) / N_ELEMENTS));
	}

	return false;
}

int CMFCAssignmentDlg::Partition(int low, int high)
{
	int pivot = m_data[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (m_data[j] <= pivot)
		{
			i++;
			std::swap(m_data[i], m_data[j]);
		}
	}
	std::swap(m_data[i + 1], m_data[high]);
	return (i + 1);
}

bool CMFCAssignmentDlg::QuickSortStep()
{
	// On first run, initialize the stack
	if (m_quickStack.empty() && m_iIndex == 0 && m_jIndex == 0)
	{
		m_quickStack.push_back({ 0, N_ELEMENTS - 1 });
	}

	if (m_quickStack.empty())
	{
		return true; // Sort is complete
	}

	// Get the next sub-problem from the stack
	int low = m_quickStack.back().first;
	int high = m_quickStack.back().second;
	m_quickStack.pop_back();

	// The Partition runs as a single step for simplicity
	m_partitionIndex = Partition(low, high);

	// Highlight the pivot's final position
	m_iCompareIndex = m_partitionIndex;
	m_jCompareIndex = -1;

	// Push right sub-array onto stack (elements > pivot)
	if (m_partitionIndex + 1 < high)
	{
		m_quickStack.push_back({ m_partitionIndex + 1, high });
	}

	// Push left sub-array onto stack (elements < pivot)
	if (m_partitionIndex - 1 > low)
	{
		m_quickStack.push_back({ low, m_partitionIndex - 1 });
	}

	// Rough progress update: inverse of stack size
	m_ctrlProgress.SetPos(min(100, 100 - (int)((m_quickStack.size() * 100.0) / N_ELEMENTS)));

	return false;
}

void CMFCAssignmentDlg::OnBnClickedBtnStartStop()
{
	if (m_data.empty() || m_iIndex >= N_ELEMENTS - 1)
	{
		OnBnClickedBtnReset();
		if (m_data.empty()) return;
	}
	if (!m_bIsSorting)
	{
		m_bIsSorting = true;
		m_Clock.Start();

		GetDlgItem(IDC_BTN_START_STOP)->SetWindowText(_T("Stop Sort"));
		SetTimer(1, 10, NULL);
	}
	else
	{
		m_bIsSorting = false;
		KillTimer(1);
		m_Clock.Stop();
		GetDlgItem(IDC_BTN_START_STOP)->SetWindowText(_T("Start Sort"));
	}
}

void CMFCAssignmentDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1 && m_bIsSorting)
	{
		bool bIsFinished = false;
		if (m_iCurrentAlgorithm == ALGO_BUBBLE)
		{
			bIsFinished = BubbleSortStep();
		}
		else if (m_iCurrentAlgorithm == ALGO_SELECTION)
		{
			bIsFinished = SelectionSortStep();
		}
		else if (m_iCurrentAlgorithm == ALGO_INSERTION)

		{

			bIsFinished = InsertionSortStep();

		}
		else if (m_iCurrentAlgorithm == ALGO_MERGE)
		{
			bIsFinished = MergeSortStep();
		}
		else if (m_iCurrentAlgorithm == ALGO_QUICK)
		{
			bIsFinished = QuickSortStep();
		}

		Invalidate(FALSE);

		if (bIsFinished)
		{
			m_bIsSorting = false;
			KillTimer(1);
			m_Clock.Stop();

			GetDlgItem(IDC_BTN_START_STOP)->SetWindowText(_T("Finished"));

			double time_ms = m_Clock.ElapsedTime();
			CString strTime;
			strTime.Format(_T("Time: %.2f ms"), time_ms);
			m_ctrlTime.SetWindowText(strTime);

			SetDlgItemText(IDC_STATIC_TIME, strTime);

			m_iCompareIndex = -1;
			m_jCompareIndex = -1;
			Invalidate(FALSE);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
void CMFCAssignmentDlg::OnCbnSelchangeCmbAlgorithm()
{
	m_iCurrentAlgorithm = m_ctrlAlgorithm.GetCurSel();

	OnBnClickedBtnReset();
}

void CMFCAssignmentDlg::OnNMCustomdrawProgressBar(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}

void CMFCAssignmentDlg::OnStnClickedStaticTime()
{
}