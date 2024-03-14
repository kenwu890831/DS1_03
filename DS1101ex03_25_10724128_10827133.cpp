// 10724128 吳宇哲 10827133 鄧梓岑
// 【工具】–【編譯選項】–【編譯器】勾選【編譯時加入以下命令】
// 加入【-std=c++11】 ，即可運作。

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <new>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std ;

struct Node{

    string data = "" ;
    struct Node *next ;

} ;

typedef struct Node node ;

node *head ;

char skipwhite() {

    char input ;
    scanf( "%c", &input ) ;
    while ( input == ' ' || input == '\t' ) scanf( "%c", &input ) ;
    return input ;

} // skipwhite()

bool isspecial( char input ) {

    if ( ( input >= '*' && input <= '+' ) || input == '-' || input == '/' )  return true ;
    return false ;

} // isspecial()

void del( Node *input ) {

    Node *current ;
    current = new Node ;
    current->next = NULL ;

    while ( input != NULL ) {

        current = input ;
        input = input->next ;
        delete current ;

    } // while

} // del

bool readlist () {

    char input ;
    bool spe = false, needoperator = false, fir = true ;
    int small = 0, middle = 0, big = 0 ;
    int numCount = 0 , specialCount = 0 ;
    node *current, *tail ;

    input = skipwhite() ;
    head = new node ;
    tail = new node ;
    head->next = NULL ;
    tail->next = NULL ;
    if ( input == '\n' ) input = skipwhite() ;
    while ( input != '\n' ) {

        current = new node ;
        current->next = NULL ;
        if ( isspecial( input ) && spe == false ) {
            spe = true ;
            needoperator = false ;
            current->data +=input ;
            specialCount++ ;

            if ( fir ) {

                cout << "Error 3 : There is one incorrect operator" << endl ;
                while ( input != '\n' ) input = skipwhite() ;
                del( tail) ;
                del( current) ;
                return false ;

            } // if
            else {

                tail->next = current ;
                tail = current ;
                tail->next = NULL ;

            } // else

            input = skipwhite() ;

        } // if
        else if ( input == '(' || input == '[' || input == '{' ) {

            current->data +=input ;
            if ( input == '(' ) small++ ;
            if ( input == '[' ) middle++ ;
            if ( input == '{' ) big++ ;
            if ( fir ) {

                head = current ;
                tail = current ;
                fir = false ;

            } // if
            else if ( spe == true ){

                tail->next = current ;
                tail = current ;
                tail->next = NULL ;

            } // else
            else {

                cout << "Error 3 : There is one extra operand" << endl ;
                while ( input != '\n' ) input = skipwhite() ;
                del( tail) ;
                del( current) ;
                return false ;

            }
            spe = true ;
            input = skipwhite() ;

        } // else if
        else if ( ( input == ')' || input == ']' || input == '}' ) && spe == false ) {

            current->data +=input ;
            needoperator = true ;
            if ( input == ')' ) small-- ;
            if ( input == ']' ) middle-- ;
            if ( input == '}' ) big-- ;
            if ( fir ) {

                cout << "Error 2 : There is one incorrect parenthesis" << endl ;
                while ( input != '\n' ) input = skipwhite() ;
                del( tail) ;
                del( current) ;
                return false ;

            } // if
            else {

                tail->next = current ;
                tail = current ;
                tail->next = NULL ;

            } // else
            input = skipwhite() ;

        } // else if
        else if ( ( input >= '0' && input <= '9' ) && needoperator == false ){
            spe = false ;
            string temp = "" ;
            while ( ( input >= '0' && input <= '9' ) ) {
                temp += input ;
                input = skipwhite() ;
            } // while
            current->data = temp ;
            numCount++ ;
            if ( fir ) {

                head = current ;
                tail = current ;
                fir = false ;

            } // if
            else {

                tail->next = current ;
                tail = current ;
                tail->next = NULL ;

            } // else

        } // else if
        else if ( needoperator ){

            cout << "Error 3 : There is one extra operand" << endl ;
            while ( input != '\n' ) input = skipwhite() ;
            del( tail) ;
            del( current) ;
            return false ;

        } // else if
        else if ( isspecial( input ) && spe == true ) {

            cout << "Error 3 : There is one extra operator" << endl ;
            while ( input != '\n' ) input = skipwhite() ;
            del( tail) ;
            del( current) ;
            return false ;

        } // else if
        else {

            cout << "Error 1 : " << input << " is not a legitimate character" << endl ;
            while ( input != '\n' ) input = skipwhite() ;
            del( tail) ;
            del( current) ;
            return false ;

        }
    } // while

    if ( small != 0 || middle != 0 || big != 0 ) {
        cout << "Error 2 : There is one extra open parenthesis" << endl ;
        return false ;
    }


    if (( numCount -  specialCount) != 1 ) {
            cout << "Error 3 : There is one extra operator" << endl ;
            while ( input != '\n' ) input = skipwhite() ;
            return false ;

        } // else if

    cout << "It is a legitimate infix expression" << endl ;
    tail = NULL ;
    current = NULL ;
    del( tail) ;
    del( current) ;
    return true ;

} // readline()


// Stack ---------------------------------------------------------------------------------------------------------------------------------

class StackList;

class StackNode{
private:
    string data; // 存的資料
    StackNode *next; // 指向下一個
public:
    StackNode() {};
    StackNode(string x){
        data = x ; // 添加資料
    }

    friend class StackList;
};

class StackList{
private:
    StackNode *top ;     // remember the address of top element
    int size;           // number of elements in Stack
public:
    StackList():size(0),top(0){};
    void Push(string x);
    void Pop();
    bool IsEmpty();
    string Top();
    int getSize();
    void destroy() ;
};

void StackList::Push(string x){

    if (IsEmpty()) {
        top = new StackNode(x);
        top -> next = NULL ;
        size++;
        return;
    }

    StackNode *newnode = new StackNode(x);  // Push_front() in Linked list
    newnode->next = top;
    top = newnode;
    size++;
}

void StackList::Pop(){

    if (IsEmpty()) {
        //std::cout << "Stack is empty.\n";
        return;
    }

    StackNode *deletenode = top;
    top = top->next;
    delete deletenode;
    deletenode = 0;
    size--;
}

bool StackList::IsEmpty(){
    if ( size == 0 ) {
        top = NULL ;
         return true;
    }
    else
        return false ;
        // if size==0, return true
}

string StackList::Top(){

    if (IsEmpty()) {
        //std::cout << "Stack is empty.\n";
        return "" ;
    }
    return top->data;
}

int StackList::getSize(){

    return size;
}

void StackList::destroy(){
    StackNode *deletenode = top;
    while (!IsEmpty()) {
            deletenode = top ;
            top = top->next;
            delete deletenode;
            deletenode = 0;
            size--;

    }
}


void readstack () {
    node *walk ;
    walk = new node() ;
    walk = head ;
    int num = 0, set = 0 ;
    bool first = true ;
    StackList operationStack ;
    while ( walk != NULL ) {
         if ( walk->data == "(" || walk->data == "[" || walk->data == "{" ){
            operationStack.Push( walk -> data ) ;
            num= 0 ;
            set = 0 ;
         }

        else if ( walk->data == "+" || walk->data == "-" || walk->data == "*" || walk->data == "/" ){

                if ( operationStack.IsEmpty())
                        operationStack.Push( walk -> data ) ;
                else if ( num == 2 &&  ( operationStack.Top() == "*" || operationStack.Top() == "/")) {
                            cout << ","<< operationStack.Top()   ;
                            operationStack.Pop() ;
                            set++ ;
                            if ( set == 2 ) {
                                cout << ","<< operationStack.Top()   ;
                                operationStack.Pop() ;
                                set = 1 ;
                            }
                            operationStack.Push( walk -> data ) ;
                            num= 0 ;

                }

                else if ( (walk->data == "*" || walk->data == "/") && ( operationStack.Top() == "*" || operationStack.Top() == "/")  ) {

                            cout << "," << operationStack.Top()  ;
                            operationStack.Pop() ;
                            set++ ;
                            if ( set == 2 ) {
                                cout << "," << operationStack.Top()  ;
                                operationStack.Pop() ;
                                set = 1 ;
                            }
                            operationStack.Push( walk -> data ) ;
                            num = 0 ;
                }
               else if ( (walk->data == "*" || walk->data == "/") && ( operationStack.Top() == "(" || operationStack.Top() == "[" || operationStack.Top() == "{" )  ) {
                    operationStack.Push( walk -> data ) ;
                }
                else if  (walk->data == "*" || walk->data == "/") {
                    operationStack.Push( walk -> data ) ;

                }
                else if ( (walk->data == "+" || walk->data == "-") && ( operationStack.Top() == "+" || operationStack.Top() == "-")  ) {

                            cout << ","<< operationStack.Top()   ;
                            operationStack.Pop() ;
                            operationStack.Push( walk -> data ) ;
                }
                else if ( (walk->data == "+" || walk->data == "-")  ) {
                        operationStack.Push( walk -> data ) ;


                }
        }
        else if ( walk->data == ")" || walk->data == "]" || walk->data == "}" ) {
            while (!( operationStack.Top() == "("|| operationStack.Top() == "[" || operationStack.Top()== "{")) {
                cout << ","<< operationStack.Top()   ;
                operationStack.Pop() ;
            }
             operationStack.Pop() ;
        }

        else {
            if ( first) {
                cout << walk -> data ;
                num++ ;
                first = false ;
            }
            else {
                cout <<","<< walk -> data ;
                num++ ;
            }

        }


         walk = walk -> next ;
    }

    while ( !operationStack.IsEmpty()) {
       cout << ","<< operationStack.Top()   ;
       operationStack.Pop() ;
    }

    operationStack.destroy() ;
} // readStack()

int main(void) {
  int command = 0 ; // user command
  do {

  	cout << endl << "*** Arithmetic Expression Evaluator ***" ;
  	cout << endl << "*   0. Quit                           *" ;
  	cout << endl << "*   1. Check infix expression         *" ;
  	cout << endl << "*   2. Infix -> postfix Evaluation    *" ;
  	cout << endl << "***************************************" ;
  	cout << endl << "Input a command( 0, 1, 2 ) :" ;
  	cin >> command ; // get the command
  	switch(command){
		case 0 : break ; //跳出，結束

  		case 1 : //檢查中序式是否正確
  			cout << endl << "Input an infix expression: " ;
  			readlist() ;
  			break ;

  		case 2 :
  			cout << endl << "Input an infix expression: " ;
  			if (readlist() )
                readstack() ;
  			cout << endl ;
  			break ;

  		default :
			cout << endl << "command does not exist !!" << endl ;
  			break ;

  			del(head)  ;
	} // end switch

  } while ( command != 0 ) ;

  system( "pause") ; // pause the display
  return 0 ;
} // main()

// (29+101)*33/25
// 24*7770/(55+30*2)  24*7770/(30*2 +55)
// (90+(70*(68-55/10)))    (90+((68-55/10)*70))
// 69/3+30*5-24/8
// 69/3+30*5-24/8+25*87
