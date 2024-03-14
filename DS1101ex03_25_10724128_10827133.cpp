//10827157 吳添聖 & 10827133 鄧梓岑 
#include <stdio.h>
#include <iostream> // cin, cout, endl
#include <cstdlib> // strtoul, system
#include <vector>
#include <string.h>


using namespace std ;

struct Formula {
	
	string data ;
	Formula *next ;
};	

Formula *head = new Formula ;
Formula *current = head ;

char temp[100] ; // 存取一開始輸入的式子 
char postfix[100] ; // 後序式

Formula *ptop = new Formula ;
Formula *post = ptop ; // 存後序式的linklist 

class stracklist {
public:
	bool isnum(char i) {
 		if( i>='0' && i<='9' ) return true ;
	 		else return false ;
	} // 檢查是否為數字 
	
	bool issymbol1(char i, int *err, char *ernum) {
	 	if( i=='+' ||i=='-'|| i=='*'|| i=='/' || i=='('|| i==')' ) return true ;
	 	else {
	 		*err = 1 ;
	 		*ernum = i ;
			return false ;
		} // 回傳錯誤的符號 
	} // 檢查是否為加減乘除
	
	bool issymbol2(char i, int *err, char *ernum) {
	 	if( i=='+' ||i=='-'|| i=='*'|| i=='/' ) return true ;
	 	else {
	 		*err = 1 ;
	 		*ernum = i ;
			return false ;
		} // 回傳錯誤的符號 
	} // 檢查是否為括弧 


		
	bool Input( int *err, char *ernum ) {
			
		head->next = NULL ; 
		
		int size ;
			
		cin.getline(temp,100);
		strcat(temp, "\n"); // 增加一個回車符號 
		
		if( analyze( temp, &*err, &*ernum ) ) return true ;
		else return false ;
	}
		
	bool analyze( char temp[100], int *err, char *ernum ){
		
	int i=0, j=0, x=0 ;
	int parentthesis=0 ; // 記錄括號 
	bool extraop = false ;
		
		do {
			if ( temp[i]!=' ' ){
				if ( isnum(temp[i]) ) {
			  		char need[100] ;
			  		
			   		for ( j=0; isnum(temp[i]); i++ ){
			    		need[j] = temp[i] ; 
			    		j++ ; // 換下一個字元 
			  	 	} // for
			  	 	
			  	 	extraop = false ; // 下一個可以是符號
			       	current->data.assign( need ) ; // 存入 current->data;	
			  		memset(need, '\0', sizeof(need)); // 初始化need記憶體		
			  	} // 放入數字
			  		
			  	else if ( issymbol1(temp[i], &*err, &*ernum) && extraop==false ){ 
			    	current->data = temp[i] ;
			    	if (temp[i]=='(') parentthesis++ ;
			    	else if (temp[i]==')') parentthesis-- ;
			    	
			    	extraop = true ; // 下一個不能是符號 
			  		i++ ; // 換下一個字元 
			  	} // 若不是數字，則放入標點符號 
		  		
		  		else if (!issymbol1(temp[i], &*err, &*ernum) && !issymbol2(temp[i], &*err, &*ernum) ){
		  			return false ; // 有不明符號，直接跳掉 
		  		}
		  		
		  		else return false ; //有不明符號 
		  		
		  		current->next = new Formula ;
		  		current = current->next ;
		  		current->next = NULL ;
		  	} // if 空白就跳掉 
	  		
	  	} while ( temp[i]!='\n' ) ; // while() 
	  	
	  	if ( issymbol2(temp[i-1], &*err, &*ernum) ){
	  		*err=4 ;
	  		return false ;
		} // 最後一個是加減乘除，輸入的式子不是一個計算式 
		
		else if (extraop ){
			*err = 3 ; 
		  	return false ; 
		} // 連續兩個符號 
		
	  	else if ( parentthesis>0 ){
			*err=21 ;
			return false ;
		} // 多左括號 
		
		else if ( parentthesis<0 ){
			*err=22 ;
			return false ;
		} // 多右括號 
		
		current->next = new Formula ;
		current = current->next ;
		current->data = '\n' ; 
		current->next = NULL ; // linklist最後給一個回車
	  	
	  	return true ;
	} // analyze()
	
	void inToPostfix () { 
	    
	    char stack[100] ; // 堆疊，存取暫時擋區
    	int i, j, top;
    	
		    for(i = 0, j = 0, top = 0; temp[i] != '\n'; i++) switch(temp[i]) { 
		        case '(':              // 運算子堆疊 
		            stack[++top] = temp[i]; 
		            break; 
		        case '+': case '-': case '*': case '/': 
		            while(priority(stack[top]) >= priority(temp[i])) { 
		                postfix[j++] = stack[top--] ;
		                cout << postfix[j-1] << ", ";
		                
		                putinpost( postfix[j-1] ) ; // 放進post linklist中 
		                nextpost() ; // 讓post linklist指向next
		            } 
		             
		            stack[++top] = temp[i]; // 存入堆疊 
		            break; 
		        case ')': 
		            while(stack[top] != '(') { // 遇 ) 輸出至 ( 
		                postfix[j++] = stack[top--] ;
		            } 
		            top--;  // 不輸出 
		            break; 
		        default:  // 運算元直接輸出 
		        	while ( isnum( temp[i])==true ) {
			            postfix[j++] = temp[i];
			            cout << temp[i] ;
			            putinpost( temp[i] ) ; // 放進post linklist中 
			            
			            if ( isnum( temp[i+1])==true )i++ ;
			            else break ;
					} // 遇到數字一次存完 
						cout << ", " ;
						nextpost() ; // 讓post linklist指向next
		    } // for
		    
		    while(top > 0) { 
		        postfix[j++] = stack[top--];
		        cout << postfix[j-1] ; // 最後一個運算子 
		        putinpost( postfix[j-1] ) ; // 放進post linklist中
		        
		        if ( top > 0 ) {
		        	cout << ", " ;
		        	nextpost() ; // 讓post linklist指向next
				}
		    }
		cout << endl ;
		nextpost() ; // 讓post linklist指向next
		post->data = '\n' ; 
		post = ptop ; // post重新指向開頭 
		
	} 

	int priority(char op) { 
	    switch(op) { 
	        case '+': case '-': return 1;
	        case '*': case '/': return 2;
	        default:            return 0;
	    } 
	}
	
	void putinpost ( char postfix ) {
		post->data = post->data + postfix ;
	}
	
	void nextpost () {
		post->next = new Formula ;
		post = post->next ;
		post->next = NULL ;
	}
	
	int eval() {
	    char opnd[2] ;
	    int stack[100] ; 
	    int ans, top=0, i=0, x=0 ; 

    		for ( ; postfix[i] != '\0'; i++) switch(postfix[i]) { 
        		case '+': case '-': case '*': case '/': 
            		stack[top-1] = cal( postfix[i], stack[top-1], stack[top]); 
            		top--; 
           		break; 
        	default: 
            	opnd[0] = postfix[i];
            	stack[++top] = atof(opnd);
    		}             
    
    return stack[100];
	}
	
	int cal(char op, int p1, int p2) { 
	    switch(op) { 
        case '+': return p1 + p2; 
        case '-': return p1 - p2; 
        case '*': return p1 * p2; 
        case '/': return p1 / p2; 
    	}
	}
}; // class 




int main (void){
	int command, err=0 ;
	char ernum ; // 抓錯的字元 
		
	do {
		stracklist strack ;
	
		cout << endl << "* Arithmetic Expression Evaluator *" ;
  		cout << endl << "* 0. QUIT                         *" ; 
  		cout << endl << "* 1. Infix2postfix Evaluation     *" ;
  		cout << endl << "* ***********************************" ;
  		cout << endl << "Input a choice(0, 1):" ;  	
  		cin >> command ; //輸入0or1指令 

		switch(command){
			case 0 : break ; //跳出，結束 
  		
  			case 1 : //檢查並算出 
  				cin.ignore(200, '\n');
  				cout << endl << "Input an infix expression: " ;
  				
  				if ( strack.Input(&err, &ernum) ) cout << "It is a legitimate infix expression." << endl ;
  				else if( err==1 ) cout << "Error 1: " << ernum << "is a legitimate character." << endl ;
  				else if( err==21 ) cout << "Error 2: there is one extra open parenthesis." << endl ;
  				else if( err==22 ) cout << "Error 2: there is one extra close parenthesis." << endl ;
  				else if( err==3 ) cout << "Error 3: there is one extra operand." << endl ;
  				else if( err==4 ) cout << "Error 4: this is not a calculation formula." << endl ;

  				cout << "Postfix expression: " ;
  				strack.inToPostfix() ; // 分類，轉後序式並且輸出至螢幕 
  				
  				cout << "Answer: " ;
  				cout << strack.eval() << endl ;
  				break ;
  			
  			default : 
			  	cout << endl << "command does not exist !!" << endl ;
  				break ;
		} // end switch
		
	}while(command!=0); // break out the loop 
  
	system ("pause") ; // 查看運作過程 
	return 0 ;
  
} //end main()
