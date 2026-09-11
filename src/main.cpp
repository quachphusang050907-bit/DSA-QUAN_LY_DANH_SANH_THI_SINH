#include <iostream>
#include <limits>

#include "include/CandidateManager.h"

using namespace std;

// ======================================================
// HIỂN THỊ MENU
// ======================================================
void displayMenu() {
    cout << "\n";
    cout << "==================================================\n";
    cout << "          CANDIDATE MANAGEMENT SYSTEM\n";
    cout << "==================================================\n";
    cout << "1. Add Candidate\n";
    cout << "2. Search Candidate\n";
    cout << "3. Display Sorted Candidates\n";
    cout << "4. Display Candidate Groups\n";
    cout << "5. Distribute Candidates to Rooms\n";
    cout << "6. Remove Candidate\n";
    cout << "0. Exit\n";
    cout << "==================================================\n";
}


// ======================================================
// MAIN
// ======================================================
int main() {

    // Tạo đối tượng quản lý chính
    CandidateManager manager;

    // Load dữ liệu từ candidates.txt
    manager.loadData("data/candidates_100.txt");

    int choice;

    do {

        displayMenu();

        cout << "Enter your choice: ";

        // Kiểm tra dữ liệu nhập vào
        if (!(cin >> choice)) {

            cout << "Invalid input! Please enter a number.\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        // Xóa dữ liệu còn lại trong input buffer
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );


        switch (choice) {

        // ==================================================
        // 1. THÊM THÍ SINH
        // ==================================================
        case 1:

            cout << "\n";
            cout << "========== ADD CANDIDATE ==========\n";

            manager.addCandidate();

            break;

// ==================================================
// 2. TÌM KIẾM THÍ SINH
// ==================================================
case 2:
{
    int searchChoice;

    do
    {
        cout << "\n";
        cout << "========== SEARCH CANDIDATE ==========\n";
        cout << "1. Search by Name\n";
        cout << "2. Search by Exam ID\n";
        cout << "0. Back\n";
        cout << "======================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> searchChoice))
        {
            cout << "Invalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        // ------------------------------------------
        // SEARCH BY NAME
        // ------------------------------------------
        if (searchChoice == 1)
        {
            string keyword;

            cout << "\nEnter candidate name: ";
            getline(cin, keyword);

            vector<Candidate> results =
                manager.searchCandidatesByName(keyword);

            if (results.empty())
            {
                cout << "No candidate found.\n";
            }
            else
            {
                cout << "\n========== SEARCH RESULTS ==========\n";

                Candidate::printHeader();
                Candidate::printSeparator();

                for (const Candidate& candidate : results)
                {
                    candidate.display();
                }
            }
        }

        // ------------------------------------------
        // SEARCH BY EXAM ID
        // ------------------------------------------
        else if (searchChoice == 2)
        {
            string examID;

            cout << "\nEnter exam ID: ";
            getline(cin, examID);

            Candidate* candidate =
                manager.searchCandidate(examID);

            if (candidate == nullptr)
            {
                cout << "No candidate found with this Exam ID.\n";
            }
            else
            {
                cout << "\n========== SEARCH RESULT ==========\n";

                Candidate::printHeader();
                Candidate::printSeparator();

                candidate->display();
            }
        }

        // ------------------------------------------
        // BACK
        // ------------------------------------------
        else if (searchChoice == 0)
        {
            cout << "Returning to main menu...\n";
        }

        else
        {
            cout << "Invalid choice! "
                 << "Please choose from 0 to 2.\n";
        }

    } while (searchChoice != 0);

    break;
}
            
        // ==================================================
        // 3. HIỂN THỊ DANH SÁCH SẮP XẾP
        // ==================================================
        case 3:

            cout << "\n";
            cout << "========== SORTED CANDIDATES ==========\n";

            manager.displaySortedCandidates();

            break;


        // ==================================================
        // 4. NHÓM THEO CHỮ CÁI
        // ==================================================
        case 4:

            cout << "\n";
            cout << "========== CANDIDATE GROUPS ==========\n";

            manager.displayGroups();

            break;


        // ==================================================
        // 5. PHÂN THÍ SINH VÀO PHÒNG
        // ==================================================
        case 5:

            cout << "\n";
            cout << "========== DISTRIBUTE TO ROOMS ==========\n";

            manager.distributeCandidatesToRooms();

            break;


        // ==================================================
        // 6. XÓA THÍ SINH
        // ==================================================
        case 6:

            cout << "\n";
            cout << "========== REMOVE CANDIDATE ==========\n";

            manager.removeCandidate();

            break;


        // ==================================================
        // 0. THOÁT
        // ==================================================
        case 0:

            cout << "\nSaving data...\n";

            manager.saveData("data/candidates_100.txt");

            cout << "Data saved successfully.\n";
            cout << "Goodbye!\n";

            break;


        // ==================================================
        // LỰA CHỌN KHÔNG HỢP LỆ
        // ==================================================
        default:

            cout << "\nInvalid choice!\n";
            cout << "Please choose from 0 to 6.\n";

            break;
        }

    } while (choice != 0);


    return 0;
}
