#include <iostream>
#include <string>
using namespace std;
struct Student {
    int studentID;
    string studentName;
    string department;
    float GPA;

};

struct AVLNode {
    Student student;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Student s) : student(s), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLNode* insert(AVLNode* node, Student student) {
    if (node == nullptr)
        return new AVLNode(student);

    if (student.studentID < node->student.studentID)
        node->left = insert(node->left, student);
    else if (student.studentID > node->student.studentID)
        node->right = insert(node->right, student);
    else
        return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && student.studentID < node->left->student.studentID)
        return rightRotate(node);

    if (balance < -1 && student.studentID > node->right->student.studentID)
        return leftRotate(node);

    if (balance > 1 && student.studentID > node->left->student.studentID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && student.studentID < node->right->student.studentID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
// to delete
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLNode* deleteNode(AVLNode* root, int studentID) {
    if (root == nullptr)
        return root;

    if (studentID < root->student.studentID)
        root->left = deleteNode(root->left, studentID);
    else if (studentID > root->student.studentID)
        root->right = deleteNode(root->right, studentID);
    else {
        if (root->left == nullptr) {
            AVLNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            AVLNode* temp = root->left;
            delete root;
            return temp;
        }

        AVLNode* temp = minValueNode(root->right);
        root->student = temp->student;
        root->right = deleteNode(root->right, temp->student.studentID);
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search function (by student ID)
AVLNode* searchByID(AVLNode* root, int studentID) {
    if (root == nullptr || root->student.studentID == studentID)
        return root;

    if (studentID < root->student.studentID)
        return searchByID(root->left, studentID);

    return searchByID(root->right, studentID);
}

// Update function
AVLNode* updateStudentInfo(AVLNode* root, int studentID, const Student& newStudentInfo) {
    AVLNode* node = searchByID(root, studentID);
    if (node) {
        node->student = newStudentInfo; // Update the student information
    }
    return root;
}


void inorder(AVLNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "Student ID: " << root->student.studentID
                  << ", Name: " << root->student.studentName
                  << ", Department: " << root->student.department
                  << ", GPA: " << root->student.GPA
                  << endl;
        inorder(root->right);
    }
}

void preorder(AVLNode* root) {
    if (root != nullptr) {
        cout << "Student ID: " << root->student.studentID
                  << ", Name: " << root->student.studentName
                 << ", Department: " << root->student.department
                  << ", GPA: " << root->student.GPA
                <<endl;
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(AVLNode* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << "Student ID: " << root->student.studentID
                  << ", Name: " << root->student.studentName
                  << ", Department: " << root->student.department
                  << ", GPA: " << root->student.GPA
                  << endl;
    }
}

int main() {
    AVLNode* root = nullptr;
    int n;
    cout << "Enter the number of students: ";
    cin >> n;
    cin.ignore();  // To clear the newline left in the buffer

    for (int i = 0; i < n; ++i) {
        Student student;

        cout << "Enter details for student " << i + 1 << ":\n";

        cout << "Student ID: ";
        cin >> student.studentID;
        cin.ignore();

        cout << "Student Name: ";
        getline(cin, student.studentName);

        cout << "Department: ";
        getline(cin, student.department);

        cout << "GPA: ";
        cin >> student.GPA;
        cin.ignore();


        root = insert(root, student);
    }

  int choice;
  do{

        cout << "\nChoose an operation:\n";
        cout << "1. Inorder Traversal\n";
        cout << "2. Preorder Traversal\n";
        cout << "3. Postorder Traversal\n";
        cout << "4. Search by ID\n";
        cout << "6. Update Student Info\n";
        cout << "7. Delete Student\n";
        cout << "8. Exit\n";
        cin >> choice;

        if (choice == 1) {
            inorder(root);
        } else if (choice == 2) {
            preorder(root);
        } else if (choice == 3) {
            postorder(root);
        } else if (choice == 4) {
            int id;
            cout << "Enter Student ID to search: ";
            cin >> id;
            AVLNode* student = searchByID(root, id);
            if (student) {
                cout << "Found Student: " << student->student.studentName << endl;
            } else {
                cout << "Student not found.\n";
            }

         } else if (choice == 6) {
            int id;
            Student newInfo;
            cout << "Enter Student ID to update: ";
            cin >> id;
            cout << "Enter new details for student (ID: " << id << "):\n";
            cout << "New GPA: ";
            cin >> newInfo.GPA;
            cin.ignore();
            root = updateStudentInfo(root, id, newInfo);
        } else if (choice == 7) {
            int id;
            cout << "Enter Student ID to delete: ";
            cin >> id;
            root = deleteNode(root, id);
        }
    } while (choice != 8);

    return 0;
}


