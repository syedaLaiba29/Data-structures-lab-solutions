#include <iostream>
using namespace std;

struct patient{
	int ID;
	patient* next;
	patient* prev;
	patient(int id)
	{
		ID=id;
		next=nullptr;
		prev=nullptr;
	}
};
class hosptal_queue
{
	public:
		patient* head;
		patient* tail;
		
		
		hosptal_queue()
		{
			head=nullptr;
			tail=nullptr;
		
		}
		void insertatbeginning(int id)
		{
			patient* node=new patient(id);
			if (head == nullptr)
			{
				head=node;
				tail=node;
			}
			if (head != nullptr)
			{
				node->next=head;
				head->prev=node;
				head=node;
			}
			cout<<"patient successfully admitted"<<endl;
		}
		void insertatend(int id)
		{
			patient* node=new patient(id);
			if (head == nullptr)
			{
				head=node;
				tail=node;
			}
			if (head != nullptr)
			{
				node->prev=tail;
				tail->next=node;
				tail=node;
			}
			cout<<"patient admitted!"<<endl;
		}
		void insertatpos(int id,int pos)
		{
			if (pos < 1)
			{
				cout<<"Patient can't be added at this Position";
				return;
			}
			if (pos == 1)
			{
				insertatbeginning(id);
			    return;
		    }
		    patient* node=new patient(id);
		    patient* curr=head;
		    for (int i;i<pos-1;i++)
		    {
		    	curr=curr->next;
			}
			node->prev = curr;
		    node->next = curr->next;
		    if (curr->next != nullptr)
		    {
			    curr->next->prev =node;
		    }
		    curr->next = node;
		    cout<<"patient admitted"<<endl;
		}
		void deletefrombeginning()
		{
			 if (head == nullptr)
			 {
			 	cout<<"No Patients";
			 	return;
			 }
			 if (head->next == nullptr)
			 {
			 	delete head;
			 	delete tail;
			 	cout<<"The patient is treated";
			 	return;
			 }
			 patient* temp=head;
			 if (head->next != nullptr)
			 {
			 	head=head->next;
			 	head->prev=nullptr;
			 	delete temp;
			 	cout<<"Patient is treated";
			 }
			 
		}
};
int main()
{
	int id,pos;
	hosptal_queue system;
	int choice;
    do {
        cout << "\n===== Hospital Emergency Queue System =====\n";
        cout << "1. Add patient to queue\n";
        cout << "2. new critical patient arrive\n";
        cout << "3. A patient discharged (delete at position)\n";
        cout << "4. treat first patient \n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout<<"Enter patient ID"<<endl;
                cin>>id;
            	system.insertatend(id);
            	break;
            	
            case 2:
            	system.deletefrombeginning();
				break;
			
			case 3:
            	cout<<"Enter the patient ID"<<endl;
            	cin>>id;
            	system.insertatbeginning(id);
				break;
				
			case 4:
            	cout<<"Enter the patient ID"<<endl;
            	cin>>id;
            	cout<<"Enter position"<<endl;
            	cin>>pos;
            	system.insertatpos(id,pos);
				break;
			
            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}
