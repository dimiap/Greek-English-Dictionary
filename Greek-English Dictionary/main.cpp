#include<iostream>
using namespace std;

//make a struct type node
typedef struct node
{
struct node *pRt,*pLf; //pRt the right node pLf the left node
string sWord,sMeaning; //sWord is the variable in which we store the word in English, sMeaning is the variable in which we store the word in Greek
}NODE;

class cQueue
{
 NODE *pQ[20];
 int iF,iR;
public:
 cQueue()
    {
  iF=iR=-1;
    }
 void fInsert(NODE*);
 NODE* fDelete();
 int fIsempty();

};
//function to put the words into the tree
void cQueue::fInsert(NODE *pT)
{
 pQ[iR++]=pT;
}
//function to delete words from the tree
NODE* cQueue::fDelete()
{
 return(pQ[iF++]);
}
//tests if the tree is empty
int cQueue::fIsempty()
{
 if(iF==iR)
 return 1;
 return 0;
}
//class cdictionary has all the function that are going to be used
class cDictionary
{
public:
    NODE* fCreate();
    void fAdd(NODE*);
    void fDelete(NODE*,string);
    void fUpdate(NODE*);
    void fDisplay(NODE*,NODE*,int);
    void fDisplayIna(NODE*);
    void fDisplayPre(NODE*);
    void fDisplayPos(NODE*);
    void fDisplayLev(NODE*);
	void fSearch(NODE*,string);
};
//the function that makes the tree together with 1 word
NODE* cDictionary::fCreate()
{
	//pRoot-->variable node root, pNn--->the word that we added as the root if it didnt exists, pCn---> the word that we add if there is a root, pParent--->pointer of the parent
    NODE *pRoot,*pNn,*pCn,*pParent;
    char cCh;
    pRoot=NULL;
    do
    {
        pNn=new NODE;
        pNn->pLf=pNn->pRt=NULL;
        cout<<"Enter word in english: ";
        cin>>pNn->sWord;
        cout<<"Enter meaning in greek: ";
        cin>>pNn->sMeaning;
        //if there isnt another word inside then pRoot equals the word that we just added
        if(pRoot==NULL)
        pRoot=pNn;
        else
        {
        	//otherwise pCn is equal to pRoot 
            pCn=pRoot;
            while(pCn)
            {
            	//if there is pCn then pParent is equal to pCn 
                pParent=pCn;
                //if the word is smaller than the previous word then we put it at the left of the tree, otherwise we put it at the right
                if(pCn->sWord<pNn->sWord)
                pCn=pCn->pRt;
                else
                pCn=pCn->pLf;

            }
            //if pParent is smaller than the word that we put then we put it at the left of the tree, otherwise we put it at the right 
            if(pParent->sWord<pNn->sWord)
            pParent->pRt=pNn;
            else
            pParent->pLf=pNn;

        }
        cout<<"Do you want to continue(y/n) : ";
         cin>>cCh;

    }while(cCh=='y'||cCh=='Y');
return pRoot;
}
//function that we put word in an already made dictionary
void cDictionary::fAdd(NODE *pRoot)
{
	//pNn the word we just put in if there is no root, pCn the word we put while there is a root, pParent the parent's pointer
    NODE *pCn,*pNn,*pParent;
    pNn=new NODE;
    //pNn left is equal to the right which is null
    pNn->pLf=pNn->pRt=NULL;
    cout<<"Enter word in english: ";
    cin>>pNn->sWord;
    cout<<"Enter meaning in greek: ";
    cin>>pNn->sMeaning;
    pCn=pRoot;
    while(pCn)
    {
    	
    	//if this word is smaller than the previous word we put in then it goes to the left of the tree otherwise to the right
        pParent=pCn;
        if(pCn->sWord<pNn->sWord)
            pCn=pCn->pRt;
        else
            pCn=pCn->pLf;
    }
    //if pParent is smaller than the word we just entered goes to the left otherwise to the right
    if(pParent->sWord<pNn->sWord)
    pParent->pRt=pNn;
    else
    pParent->pLf=pNn;
    cout<<"Word is added succesfully to the dictionary\n";


}
//for searching the word
void cDictionary::fSearch(NODE *pPtr,string sData)
{
	//pPtr is the pointer of the word
	//if the word we gave is equal to any other word we have given
	if(pPtr->sWord==sData){
		cout<<"Node is found!";
	    cout<<pPtr->sWord<<"->"<<pPtr->sMeaning<<" ";
	}
	//an den einai isi me kapoia leksi p tou exoume dosei 
	else{
		cout<<"Node not found!";
	}
} 
//for deleting a word
void cDictionary::fDelete(NODE *pPtr,string sData)
{
    NODE *pParent;
    while(pPtr)
    {
    	//pPtr is the pointer of the word
		//if the word we gave is equal to any other word we have given	
	    if(pPtr->sWord==sData)
	    	break;
	    pParent=pPtr;
	    //if the word we have given is less than the word we see in the dictionary go left otherwise right
	    if(pPtr->sWord<sData)
	    	pPtr=pPtr->pRt;
	    else
	    	pPtr=pPtr->pLf;
    }
        //if the node we want to delete is a leaf node
        if(pPtr->pLf==NULL&&pPtr->pRt==NULL)
        {
            if(pParent->pRt==pPtr)
            	pParent->pRt=NULL;
            else
            	pParent->pLf=NULL;
            delete(pPtr);
            cout<<"Node is deleted !\n";

        }

        //if the node we want to delete has 1 child
        else if(pPtr->pLf==NULL)
        {
            if(pParent->pRt==pPtr)
            pParent->pRt=pPtr->pRt;
            else
            pParent->pLf=pPtr->pRt;
            delete(pPtr);
            cout<<"Node is deleted !\n";

        }

        else if(pPtr->pRt==NULL)
        {
            if(pParent->pRt==pPtr)
            pParent->pRt=pPtr->pLf;
            else
            pParent->pLf=pPtr->pLf;
            delete(pPtr);
            cout<<"Node is deleted !\n";

        }

        //if the node we want to delete has 2 children
        else
        {
         pParent=pPtr;
         NODE *pTemp;
         pTemp=pPtr->pRt;
         while(pTemp->pLf)
         {
          pParent=pTemp;
          pTemp=pTemp->pLf;
         }
         pPtr->sWord=pTemp->sWord;
         pPtr->sMeaning=pTemp->sMeaning;
         if(pParent==pPtr)
         pPtr->pRt=pTemp->pRt;
         else
         pParent->pLf=NULL;
         delete(pTemp);
         cout<<"Node is deleted !\n";

        }

}

//to update the meaning of a word
void cDictionary::fUpdate(NODE *pRoot)
{
    NODE *pCn;
    string sW;
    cout<<"Enter english word to update : ";
    cin>>sW;
    pCn=pRoot;
    while(pCn)
    {
    	//we find the word
        if(pCn->sWord==sW)
        {
        	//update its meaning
            cout<<"Enter new meaning in greek : ";
            cin>>pCn->sMeaning;
            cout<<"Meaning updated succesfully\n";
            return;
        }
        else
        {
        	//if the word is larger than the current word then go to the right node otherwise left
	        if(pCn->sWord<sW)
	        	pCn=pCn->pRt;
	        else
	        	pCn=pCn->pLf;
        }

    }
cout<<"Word not found!\n";
}
//to print the nodes as a tree
void cDictionary::fDisplay(NODE *pRoot,NODE *pPtr, int level)
{
	int i;
	//if we find a word
	if(pPtr!=NULL)
	{
		//move on a level
		fDisplay(pRoot,pPtr->pRt, level+1);
		cout<<endl;
		if (pPtr == pRoot)
		//to see which is the root
			cout<<"Root->:  ";
	else
	{
		//for all the levels read fill with zeros
		for (i = 0;i < level;i++)
		cout<<"       ";
	}
	//print words
	cout<<pPtr->sWord<<"->"<<pPtr->sMeaning;
	fDisplay(pRoot,pPtr->pLf, level+1);
	}
}

//to print the nodes with inorder
void cDictionary::fDisplayIna(NODE *pPtr)
{
    if(pPtr)
    {
        fDisplayIna(pPtr->pLf);
        cout<<pPtr->sWord<<"->"<<pPtr->sMeaning<<"\n";
        fDisplayIna(pPtr->pRt);

    }

}
//to print the nodes with preorder
void cDictionary::fDisplayPre(NODE *pPtr)
{
	if(pPtr!=NULL)
	{
		cout<<pPtr->sWord<<"->"<<pPtr->sMeaning<<" ";
		fDisplayPre(pPtr->pLf);
		fDisplayPos(pPtr->pRt);
	}
}
//to print the nodes with postorder
void cDictionary::fDisplayPos(NODE *pPtr)
{
	if(pPtr!=NULL)
	{
		fDisplayPos(pPtr->pLf);
		fDisplayPos(pPtr->pRt);
		cout<<pPtr->sWord<<"->"<<pPtr->sMeaning<<" ";
	}
}
//to print the nodes with level order
void cDictionary::fDisplayLev(NODE *pPtr)
{
 cQueue oObj;
 NODE *pT;
 oObj.fInsert(pPtr);
 while(oObj.fIsempty()==0)
 {
  pT=oObj.fDelete();
  cout<<pT->sWord<<"->"<<pT->sMeaning<<"\n";
  if(pT->pLf)
  oObj.fInsert(pT->pLf);
  if(pT->pRt)
  oObj.fInsert(pT->pRt);
 }

}

int main()
{
    NODE *pRoot;
    string sW;
    cDictionary oObj;
    char cCh;
    int iCh;
    //the start menu  
    do
    {
     cout<<"\n\n";
        cout<<"1]Create dictionary\n";
        cout<<"2]Add new Word to the Dictionary\n";
        cout<<"3]Update Meaning of a Word in greek\n";
        cout<<"4]Find word in english\n";
        cout<<"5]Delete a word from Dictionary\n";
        cout<<"6]Display Dictionary Inorder\n";
        cout<<"7]Display Dictionary Preorder\n";
        cout<<"8]Display Dictionary Postorder\n";
        cout<<"9]Display Dictionary Levelorder\n";
        cout<<"10]Display Tree like structure\n";
        cout<<"\n\nEnter your Choice : ";
        cin>>iCh;
        switch(iCh)
        {
        case 1:
            pRoot=oObj.fCreate();
            break;

        case 2:
            oObj.fAdd(pRoot);
            break;

        case 3:
            oObj.fUpdate(pRoot);
            break;
		
		case 4:
			cout<<"Enter english word to find: ";
			cin>>sW;
			oObj.fSearch(pRoot,sW);
			break;
			
        case 5:
            cout<<"Enter english word to delete : ";
            cin>>sW;
            oObj.fDelete(pRoot,sW);
            break;
            
        case 6:
            oObj.fDisplayIna(pRoot);
            break;

        case 7:
         	oObj.fDisplayPre(pRoot);
            break;
            
        case 8:
            oObj.fDisplayPos(pRoot);
            break;
            
        case 9:
	        oObj.fDisplayLev(pRoot);
	      	break;
        
		case 10:
          	oObj.fDisplay(pRoot,pRoot,1);
            break;
        }
        cout<<"\npress 1 for main and 2 to exit ";
        cin>>cCh;
    }while(cCh=='1');

return 0;
}
