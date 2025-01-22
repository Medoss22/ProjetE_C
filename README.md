# Banking Management System

This project is a Banking Management System implemented in C. It provides functionalities for managing user and administrator accounts, handling financial transactions, and ensuring secure authentication. Below is an overview of the main features.

## Features

### 1. Account Management
- **registerAccount**: Registers a new user account and associates a password.
  - Generates a unique account number.
  - Collects user information and stores it in a CSV file.
  - Associates the account with a password stored in a separate file.
  - Displays a confirmation message with the generated account number.
- **displayAccounts**: Displays all registered accounts line by line from a CSV file.
- **modifyAcc**: Allows modification of specific account details in the CSV file.
- **delete_client**: Deletes a specific user account based on the account number.

### 2. Financial Transactions
- **transfert**: Facilitates money transfers between two bank accounts stored in a CSV file.
- **makeDeposit**: Allows users to deposit money into a specific bank account.
  - Updates the account balance in the CSV file.
- **makeWithdrawal**: Enables withdrawals from a specific bank account.
  - Updates the account balance in the CSV file.

### 3. Account Search
- **recherche_Compte**: Searches for a specific account based on its account number in the CSV file.

### 4. Authentication
- **loge_in**: Manages user authentication for both administrators and standard users.
  - Supports separate login functionalities for administrators and users.
- **s_admin**: Registers a new administrator.
  - Collects administrator details, stores them in a file, and associates a password.

### 5. Application Interface
- **Start**: Implements the core banking application logic.
  - Provides an interactive menu for administrators and clients.

## How to Run
1. Clone the repository.
2. Compile the C files using a C compiler (e.g., `gcc`).
3. Run the executable to interact with the system.

## Dependencies
- Requires a C compiler.
- Data is stored in CSV files for persistence.

## License
This project is licensed under the [MIT License](LICENSE).

---

Feel free to update or adapt this draft according to your specific project details or preferences! If you need additional customization or help, let me know.
