#include "Dictionary.h"

/******************************************************************************
 * Name    : Dictionary
 * Purpose : A default constructor that sets the intial values of the Trie and 
						 creates a new Trie.
 * Inputs  : None
 * Outputs : None.
 ******************************************************************************/
 
Dictionary::Dictionary()
{
	root = nullptr;
	lastAccessed = nullptr;
	root = createTrie();
	root->word ="";
	root->definition="";
}

/******************************************************************************
 * Name    : ~Dictionary
 * Purpose : A destructor that deletes all the nodes on the stack by calling 
						 the deleteTrie() function.
 * Inputs  : None
 * Outputs : None.
 ******************************************************************************/
 
Dictionary::~Dictionary()
{
	deleteTrie(root);
}

/******************************************************************************
 * Name    : createTrie
 * Purpose : To create tries as needed starting with the root.
 * Inputs  : None
 * Outputs : Returns the trie that was just created. ******************************************************************************/
 
Dictionary::Trie Dictionary::createTrie()
{
	if(root == nullptr)
	{
		root = new TrieNode;
		lastAccessed = root;
		
		for(int i = 0; i < ALPHABET_SIZE; i++)
		{
			root->next[i] = nullptr;
		}
	}	
	else
	{		
		lastAccessed->next[creationIndex] = new TrieNode;
		lastAccessed  = lastAccessed->next[creationIndex];

		for(int i = 0; i < ALPHABET_SIZE; i++)
		{
			lastAccessed->next[i] = nullptr;
		}
	}
	
	return lastAccessed;
}

/******************************************************************************
 * Name    : insertTrie
 * Purpose : To determine if a trie is to be created and where it should be
						 created. It also checks for duplicates.
 * Inputs  : Two strings containing the word and definition.
 * Outputs : Returns true if a trie was succesfully created, otherwise false.
 ******************************************************************************/

bool Dictionary::insertTrie(string word, string definition)
{
	int wordSize = word.length();
	int* digit = new int[wordSize];
	string levels ="", lowerWord = "";
	Trie temp;
	lastAccessed = root;
	
	//This loop creates a string of lowercase characters.
	for(int i = 0; i < wordSize; i++)
	{
		lowerWord += tolower(word[i]);
	}
	
	//This loop finds the corresponding number for each digit. From [a-z] to [1-26].
	for(int i = 0; i < wordSize; i++)
	{
		int asciiCode = 97;
		
		for(int j = 0; j < ALPHABET_SIZE; j++)
		{
			if(asciiCode == static_cast<int>(lowerWord[i]))
			{
				digit[i] = j;
				break;
			}
			else
			{
				asciiCode++;
			}
		}
	}
	
	//This loop determines whether a trie needs to be created.
	for(int k = 0; k < (wordSize - 1); k++)
	{
		levels = "";
		creationIndex = digit[k];
		temp = lastAccessed;
		lastAccessed = lastAccessed->next[creationIndex];
		
		for(int l = 0; l < (k + 1); l++)
		{
			levels += word[l];
		}
		
		if(lastAccessed == nullptr)
		{
			lastAccessed = temp;
			lastAccessed = createTrie();
			lastAccessed->word = levels;
		}		
	}
		
	//This is where i determine if the insertion was succesful
	creationIndex = digit[wordSize - 1];
	temp = lastAccessed;
	lastAccessed = lastAccessed->next[creationIndex];
	
	if(lastAccessed == nullptr)
	{
		lastAccessed = temp;
		lastAccessed = createTrie();
		lastAccessed->word = word;
		lastAccessed->definition = definition;
		lastAccessed = root;
		
		delete[] digit;
		return true;
	}
	
	//If the size of the definition is greater than 0. Then we have a duplicate.
	if(lastAccessed->definition.length() == 0)
	{
		lastAccessed->definition = definition;
		lastAccessed = root;
		
		delete digit;
		return true;
	}
	else
	{
		lastAccessed = root;
		
		delete digit;
		return false;
	}
}

/******************************************************************************
 * Name    : loadDictionary
 * Purpose : To insert words from a text file onto the trie
 * Inputs  : The file name.
 * Outputs : Returns true if the dictionary was succesfully loaded, else false.
 ******************************************************************************/

bool Dictionary::loadDictionary(string fileName)
{
	int stringSize, totWords = 0, sucWords = 0;
	string full, word, definition;
	fstream input;
	
	input.open(fileName.c_str(), ios::in);
	
	if(!(input.is_open()))
	{
		return false;
	}
	
	while(getline(input, full))
	{
		word = "";
		definition = "";
		stringSize = full.length();
		
		for(int i = 0; i < stringSize; i++)
		{
			if(full[i] == ':')
			{
				for(int j = 0; j < i; j++)
				{
					word += full[j];
				}
				
				for(int k = i; k < stringSize; k++)
				{
					if(isalpha(full[k]))
					{
						for(int l = k; l < stringSize; l++)
						{
							definition += full[l];
						}
						
						totWords++;
						break;
					}
				}
				
				break;
			}
		}

		if(insertTrie(word, definition))
		{
			sucWords++;
		}
	}
	
	input.close();
	
	if(sucWords == totWords)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************
 * Name    : lookup
 * Purpose : To find a certain string within the trie
 * Inputs  : A string containing the word you want to look for
 * Outputs : It returns the definition if the word is found. If it is not found
						 an empty string is returned
 ******************************************************************************/

string Dictionary::lookup(string word)
{
	int partSize, wordSize = word.length();
	string part;
	lastAccessed = root;
	
	for(int i = 0; i < wordSize; i++)
	{
		part = "";
		
		for(int j = 0; j < (i + 1); j++)
		{
			part += word[j];
		}
		
		partSize = part.length();
		
		for(int k = 0; k < ALPHABET_SIZE; k++)
		{
			if(lastAccessed->next[k] != nullptr)
			{
				reverse = lastAccessed;
				lastAccessed = lastAccessed->next[k];
				
				if(partSize > wordSize)
				{
					lastAccessed = root;
					return "";
				}
				
				if(lastAccessed->word == word)
				{
					part = lastAccessed->definition;
					lastAccessed = root;
					return part;
				}
				
				if(lastAccessed->word !=  part)
				{
					lastAccessed = reverse;
				}				
			}
		}
	}

	lastAccessed = root;
	
	return "";
}

/******************************************************************************
 * Name    : deleteTrie
 * Purpose : To delete each trie that has been created. 
 * Inputs  : The trie you wish to start deleting from(usually root). This 
						 function should only be called by the destructor.
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void Dictionary::deleteTrie(Trie traverse)
{
	for(int i = 0; i < ALPHABET_SIZE; i++)
	{
		if(traverse->next[i] != nullptr)
		{
			deleteTrie(traverse->next[i]);
		}
	}	
	
	delete traverse;
}

/******************************************************************************
 * Name    : displayTrie
 * Purpose : To call the printNode() function.
 * Inputs  : None
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void Dictionary::displayTrie()
{
	printNode(root);
}

/******************************************************************************
 * Name    : printNode
 * Purpose : To display the words in the trie using pre-order traversal
 * Inputs  : The trie you wish to start printing from(usually root).  This 
						 function should only be called by displayTrie().
 * Outputs : Nothing
 ******************************************************************************/
 
void Dictionary::printNode(Trie traverse)
{	
	if(traverse != root)
	{
		cout<<traverse->word<<": "<<traverse->definition<<endl;
	}
	
	for(int i = 0; i < ALPHABET_SIZE; i++)
	{
		if(traverse->next[i] != nullptr)
		{
			printNode(traverse->next[i]);
		}
	}
}

/******************************************************************************
 * Name    : writeTrie
 * Purpose : To write the contents of the trie onto a new file
 * Inputs  : A string containing the fileName
 * Outputs : Returns true if the writing was succesful, otherwise false.
 ******************************************************************************/
 
bool Dictionary::writeTrie(string fileName)
{
	string def, word;	
	
	outTrie(root);
	
	fstream output;
	output.open(fileName.c_str(), ios::out);	
	
	
	if(output.is_open())
	{
		//This loop outputs all the contents of the dictionary in pre-order 
		while(!(outWord.empty()))
		{
			word = outWord.front();
			def = outDef.front();
			
			output<<word<<": ";
			output<<def<<endl;
			
			outWord.pop();
			outDef.pop();
		}
		
		output.close();
		return true;
	}
	else
	{
		return false;
	}

}

/******************************************************************************
 * Name    : outTrie
 * Purpose : To hold values that were used in the trie.
 * Inputs  : The trie you wish to start printing from(usually root).  This 
						 function should only be called by writeTrie().
 * Outputs : Returns nothing.
 ******************************************************************************/
 
void Dictionary::outTrie(Trie traverse)
{
	if(traverse != root)
	{
		outWord.push(traverse->word);
		outDef.push(traverse->definition);
	}
	
	for(int i = 0; i < ALPHABET_SIZE; i++)
	{
		if(traverse->next[i] != nullptr)
		{
			outTrie(traverse->next[i]);
		}
	}
}

