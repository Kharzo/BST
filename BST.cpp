/*
 * Author: Joseph Kharzo
 * Date: 7/8/2022
 * Description: This program parses through a text file and outputs some statistics related to the file such as
 * word count and if a word is found in the file.
 */

// Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// The node class for the tree
class Node{
	public:
		// The required variables
		string data;
		Node* left;
		Node* right;
		
		// Constructor
		Node(string data){
			this->data = data;
			left = NULL;
			right = NULL;
		}
		
		// Destructor
		~Node(){
			
		}
		
		// Converts the tree into an array
		int ToArray(Node* node, string arr[], int index){
			// Checks if the initial node is null
			if(node == NULL){
				return 0;
			}	
			
			// if the node is not null
			// then the index argument is used as the index of the array
			// the data is saved in the array at the index
			// then the index is incremented
			arr[index] = node->getData();
			index++;
			
			// Checks if the next two nodes are null
			// if they are not
			// then the function calls itself with the root node being the next node
			if(node->right != NULL){
				index = ToArray(node->right, arr, index);
			}
			if(node->left != NULL){
				index = ToArray(node->left, arr, index);
			}
			
			return index;
		}
		
		// A new node is created using the constructor with given data
		Node* Insert(Node* node, string data){
			if(node == NULL){
				return new Node(data);
			}
			//cout << "Passed the null check" << endl;	
			if(data.compare(node->getData()) < 0){
				//cout << "Smaller" << endl;
				node->left = Insert(node->left, data);
			}else if(data.compare(node->getData()) > 0){
				//cout << "Larger" << endl;
				node->right = Insert(node->right, data);
			}else{
				// Equal
				// My attempts at tracking the word count used two vectors
				// and would add a word and count up its corresponding index in a different vector
				/*
				int count = 0;
				tracker.push_back(node->getData());
				for(string word:tracker){
					if(string.compare(node->getData()) == 0){
						frquency[count] = frquency[count] + 1;
					}
				}
				*/
			}
			return node;
			
		}
		
		// A node is removed and replaced by the left node of the next right node
		Node* Remove(Node* node, string data){
			if(node == NULL){
				return node;
			}
			
			// If the data being removed is smaller then it moves to the left node
			if(data.compare(node->getData()) < 0){
				node->left = Remove(node->left, data);
			}else if(data.compare(node->getData())>0){ // if it is larger
				node->right = Remove(node->right, data);
			}else{
				// if the data has been found and there are no children nodes
				if(node->left == NULL && node->right == NULL){
					return NULL;
				}else if(node->left == NULL){ // if there is only one node, in the right
					Node* tempNode = node->right;
					delete(node);
					return tempNode;
					
				}else if(node->right == NULL){ // if there is only one node, in the left
					Node* tempNode = node->left;
					delete(node);
					return tempNode;
				}else{
					// If there are two children
					// then the method talked about at the top of the function is used
					Node* tempNode = node;
					
					while(tempNode != NULL && tempNode->right != NULL){
						tempNode = tempNode->right;	
					}
					
					node->data = tempNode->data;

					node->right = Remove(node->right, tempNode->data);
					
				}
				
				
			}

			
		}	
		
		// Deletes all the elements of the node	
		// I believe the logic here is flawed
		// I was not sure how to move through the tree in the appropriate manner
		// I should most lkely use postorder traversal and go through the tree like that
		// deleting the elements acurately
		void Empty(Node* node){
			if(node == NULL){
				// If the node is null, then stop calling the function
			}else{
				// If the current node has data
				// Then move to the children
				Empty(node->left);
				Empty(node->right);	
				delete(node);
			}
				
		}
		
		//Checks if a certain string exists in the bst
		bool ElementExists(Node* node, string data){
			// if the data is found
			if(data.compare(node->getData()) == 0){
				return true;
			}
			// if the data is smaller
			// move to the left
			if(data.compare(node->getData()) < 0  && node->left != NULL){
				return ElementExists(node->left, data);
			}
			// if the data is larger
			// move to the right
			if(data.compare(node->getData()) > 0 && node->right != NULL){
				return ElementExists(node->right, data);
			}

			// the element was not found in the bst
			return false;
		}
		
		// Counts how many nodes exist
		int Count(Node* node, int count){
			if(node == NULL){
				return 0;
			}
			// The left node exists
			if(node->left != NULL){
				count++;
				count = Count(node->left,count);
			}
			// The right node exists
			if(node->right != NULL){
				count++;
				count = Count(node->right, count);
			}
			return count;
		}
		
		// Finds a spcific node in the tree
		Node* Find(Node* node, string data){
			// This uses the same logic as the other traveresal methods
			if(data.compare(node->getData()) == 0){
				return node;
			}
			if(node->left != NULL){
				return Find(node->left, data);
			}
			if(node->right != NULL){
				return Find(node->right, data);
			}
			return node;
			
		}
		
		// Gets the data within the node	
		string getData(){
			return data;
		}
		
};



int main(){
	
	// The required variables	
	bool keepRunning = true;

	int wordCount = 0;

	string textFile;
	string word;
	string lowerWord = "";

	vector<int> frequency;
	vector<string> wordTracker;

	// Asks the user for a file
	cout << "Please enter a text file (example.txt): ";
	cin >> textFile;
	ifstream ReadFile(textFile);
	
	// Creates a root node
	// Then makes it null
	Node* root = new Node("Root");
	root->Remove(root,"Root");

	// Reads text from a file
	// The letters in the file are lower cased character by character
	while(getline(ReadFile, word, ' ')){
		for(char& letter:word){
			letter = tolower(letter);
			lowerWord = lowerWord + letter;
		}
		wordCount++;
		root->Insert(root,word);
	}
	
	// An example of how to use the ToArray function
	
	
	const int SIZE = root->Count(root, 1);
	/*	
	string bst[SIZE];
	root->ToArray(root, bst, 0);
	for(int i = 0; i < SIZE; i++){
		cout << bst[i] << endl;
	}
	*/
	
	// Write to a file
	ofstream WriteFile("Kharzo_stats.txt");
	
	// Some examples to the check the text file that was read from
	WriteFile << "The total number of unique words is: " << SIZE << endl;
	WriteFile << "The total word count is: " << wordCount << endl;
	if(root->ElementExists(root, "the")){
		WriteFile << "The word 'the' is in the file!" << endl;
	}else{
		WriteFile << "The word 'the' is not in the file!" << endl;
	}

	return 0;
}
