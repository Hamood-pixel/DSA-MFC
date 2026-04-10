// MFCassignmentDlg.h : header file
//

#pragma once
#include <vector>
#include <chrono>
#include <utility> // For std::pair

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

struct msClock
{
    typedef std::chrono::high_resolution_clock clock;
    std::chrono::time_point<clock> t1, t2;
    void Start() { t1 = high_resolution_clock::now(); }
    void Stop() { t2 = high_resolution_clock::now(); }
    double ElapsedTime()
    {
        duration<double> ms_doubleC = t2 - t1;
        return ms_doubleC.count() * 1000.0;
    }
};


// CMFCAssignmentDlg dialog
class CMFCAssignmentDlg : public CDialogEx
{
public:
    CMFCAssignmentDlg(CWnd* pParent = nullptr);

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCASSIGNMENT_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

private:
    std::vector<int> m_data;
    const int N_ELEMENTS = 100;

    int m_iIndex = 0;
    int m_jIndex = 0;
    int m_kIndex = 0;

    // Merge Sort Variables
    int m_mergeSize = 1;
    int m_low = 0;
    std::vector<int> m_mergeHelper;

    // Quick Sort Variables
    std::vector<std::pair<int, int>> m_quickStack;
    int m_partitionIndex = 0;

    bool m_bIsSorting = false;

    int m_iCurrentAlgorithm = 0;
    enum SortAlgorithm { ALGO_BUBBLE, ALGO_SELECTION, ALGO_INSERTION, ALGO_MERGE, ALGO_QUICK };

    int m_iCompareIndex = -1;
    int m_jCompareIndex = -1;

    msClock m_Clock;

    CProgressCtrl m_ctrlProgress;
    CStatic m_ctrlTime;
    CComboBox m_ctrlAlgorithm;

    bool BubbleSortStep();
    bool SelectionSortStep();
    bool InsertionSortStep();
    bool MergeSortStep();
    bool QuickSortStep();

    // Quick Sort Helper
    int Partition(int low, int high);

public:
    afx_msg void OnBnClickedBtnStartStop();
    afx_msg void OnBnClickedBtnReset();
    afx_msg void OnTimer(UINT_PTR nIDEvent);


    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNMCustomdrawProgressBar(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnStnClickedStaticTime();
    afx_msg void OnCbnSelchangeCmbAlgorithm();
};