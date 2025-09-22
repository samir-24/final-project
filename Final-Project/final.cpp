#include <iostream>
#include <vector>
using namespace std;


struct Node
{
    int data;
    Node *next;
    Node(int v)
    {
        data = v;
        next = NULL;
    }
};

class LinkedList
{
    Node *head;

public:
    LinkedList() { head = NULL; }

    void insertFront(int value)
    {
        Node *n = new Node(value);
        n->next = head;
        head = n;
        cout << "Inserted " << value << " at the FRONT of the list.\n";
    }

    void insertEnd(int value)
    {
        Node *n = new Node(value);
        if (head == NULL)
        {
            head = n;
            cout << "Inserted " << value << " as the FIRST node in the list.\n";
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
        cout << "Inserted " << value << " at the END of the list.\n";
    }

    void deleteValue(int value)
    {
        if (head == NULL)
        {
            cout << "List is empty, nothing to delete.\n";
            return;
        }
        if (head->data == value)
        {
            Node *del = head;
            head = head->next;
            delete del;
            cout << "Deleted value " << value << " from the list.\n";
            return;
        }
        Node *temp = head;
        while (temp->next != NULL && temp->next->data != value)
            temp = temp->next;
        if (temp->next != NULL)
        {
            Node *del = temp->next;
            temp->next = temp->next->next;
            delete del;
            cout << "Deleted value " << value << " from the list.\n";
        }
        else
        {
            cout << "Value " << value << " not found in the list.\n";
        }
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "Linked List is empty.\n";
            return;
        }
        cout << "Current Linked List: ";
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};


void merge(vector<int> &a, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
}

void mergeSort(vector<int> &a, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}


int partition(vector<int> &a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int> &a, int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}


int binarySearch(const vector<int> &a, int x)
{
    int l = 0, r = (int)a.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (a[mid] == x)
            return mid;
        else if (a[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}


int main()
{
    LinkedList list;
    vector<int> arr; 
    int choice;

    do
    {
        cout << endl;
        cout << "==== MAIN MENU ====" << endl;
        cout << "1. Linked List Operations" << endl;
        cout << "2. Sorting" << endl;
        cout << "3. Binary Search" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int ch, val;
            do
            {
                cout << endl;
                cout << "-- Linked List Menu --" << endl;
                cout << "1. Insert Front" << endl;
                cout << "2. Insert End" << endl;
                cout << "3. Delete Value" << endl;
                cout << "4. Display List" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "Enter choice: ";
                cin >> ch;

                if (ch == 1)
                {
                    cout << "Enter value to insert at front: ";
                    cin >> val;
                    list.insertFront(val);
                }
                else if (ch == 2)
                {
                    cout << "Enter value to insert at end: ";
                    cin >> val;
                    list.insertEnd(val);
                }
                else if (ch == 3)
                {
                    cout << "Enter value to delete: ";
                    cin >> val;
                    list.deleteValue(val);
                }
                else if (ch == 4)
                {
                    list.display();
                }
            } while (ch != 5);
        }
        else if (choice == 2)
        {
            int n;
            if (arr.empty())
            {
                cout << "How many numbers? ";
                cin >> n;
                arr.resize(n);
                cout << "Enter numbers: ";
                for (int i = 0; i < n; i++)
                    cin >> arr[i];
            }
            else
            {
                cout << "Array already has " << arr.size()
                     << " numbers. Re-enter? (1 = yes / 0 = no): ";
                int re;
                cin >> re;
                if (re == 1)
                {
                    cout << "How many numbers? ";
                    cin >> n;
                    arr.resize(n);
                    cout << "Enter numbers: ";
                    for (int i = 0; i < n; i++)
                        cin >> arr[i];
                }
            }

            cout << "1. Merge Sort\n 2. Quick Sort\nChoose sorting method: ";
            int sortChoice;
            cin >> sortChoice;

            if (sortChoice == 1)
            {
                mergeSort(arr, 0, (int)arr.size() - 1);
                cout << "Array sorted using Merge Sort." << endl;
            }
            else
            {
                quickSort(arr, 0, (int)arr.size() - 1);
                cout << "Array sorted using Quick Sort." << endl;
            }

            cout << "Sorted array: ";
            for (int x : arr)
                cout << x << " ";
            cout << endl;
        }
        else if (choice == 3)
        {
            if (arr.empty())
            {
                cout << "Please sort an array first." << endl;
            }
            else
            {
                int key;
                cout << "Enter value to search: ";
                cin >> key;
                int pos = binarySearch(arr, key);
                if (pos == -1)
                    cout << "Value " << key << " not found in the array." << endl;
                else
                    cout << "Value " << key << " found at index " << pos << "." << endl;
            }
        }

    } while (choice != 4);

    cout << "Program finished." << endl;
    return 0;
}
