//(generations of all sawtooth corteges on variety{0,1} length k) with using diferent parallezing strategies
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <omp.h>
#include <ctime>



bool check(std::vector <bool> &v);
void algorithm_fst(std::vector <bool> &v);
void binary(char* ,int);
void algorithm (std::vector <std::string> &vect, std::vector <std::string> &vect1, int n, int sum_clen, int z_len, int o_len, int ptr_len, int cur_len);
void ran_algorithm(int , int ,int);

#define GETBIT(x,pos)   ( ((x) & ( 0x1 << (pos) )) !=0 )


int main()
{
	// sc - текущий размер матрицы, zl = кол-во эл тов конч на ноль,
    //ol - кол-во эл тов конч на 1 ,n - длина посл., pl - индекс последнего
	//cur_len - текущая длина
    int n, sum_clen, z_len, o_len, ptr_len, cur_len ;
    double res;
	clock_t start,end;

    std::cout << "Enter power of your cortege :) :  " << std::endl;
    std::cin >> n;

    std::vector <std::string> matr1 ;
    std::vector <std::string> matr2 ;
    
	if(n%2 == 1)
	{
    matr1.push_back("000"); //000
    matr1.push_back("010"); //010
    matr1.push_back("011"); //011
    matr1.push_back("111"); //111 [nm of el] [nm of el in els]
    
    z_len = o_len = 2;
    sum_clen = z_len + o_len;
    ptr_len = 2;
    cur_len = 3;
    
    start = clock();	
    
    algorithm(matr1, matr2, n, sum_clen, z_len, o_len, ptr_len, cur_len);
    //ran_algorithm(n,ptr_len,cur_len);
    end = clock();
    std::cout << std::endl;
    std::cout << "time of algorithm work: "<< ((double) end - start) / ((double) CLOCKS_PER_SEC);
	
	}
	
	else
	{
		
	matr1.push_back("00"); //000
    matr1.push_back("01"); //010
    matr1.push_back("11"); //010
    z_len = 1;
    o_len = 2;
    sum_clen = z_len + o_len;
    ptr_len = 1;
    cur_len = 2;
    
    start = clock();	
    
    algorithm(matr1, matr2, n, sum_clen, z_len, o_len, ptr_len, cur_len);
    //ran_algorithm(n, ptr_len, cur_len);
    end = clock();
    std::cout << std::endl;
    std::cout << "time of algorithm work: "<< ((double) end - start) / ((double) CLOCKS_PER_SEC);
    
    
	
	}
	
}

bool check(std::vector <bool> &v)

{
    for (int i = 1; i < v.size()-1; i = i+2)
    {
        if (v[i] < v[i-1])
        {
           return 0;
        }
        if  (v[i] < v[i+1])
        {
            return 0;
        }
     }

    for (int i = 0 ; i < v.size(); i++  )
    {
        std::cout << v[i];
    }

    std::cout << std::endl;
    return 1;
    
}

void algorithm (std::vector <std::string> &vect, std::vector <std::string> &vect1, int n, int sum_clen, int z_len, int o_len, int ptr_len, int cur_len)
{
	
	const std::string a = "00", b = "10", c = "11", d = "01";
	#pragma omp paralel for shedule(guided,4)
	for (int i = 0; i < sum_clen; i++)
    {
	    if(cur_len >= n) break; 
        if(((int)vect[i][ptr_len]) == 48) //if last el is zero
        {
        	if(n%2==1)
        	{
	        	std::string cur = "";
	            cur.append(vect[i]);
	            cur.append(a);
	
	            std::string cur1 = "";
	            cur1.append(vect[i]);
	            cur1.append(b);
	
	            std::string cur2 = "";
	            cur2.append(vect[i]);
	            cur2.append(c);
	
	            vect1.push_back(cur);
	            vect1.push_back(cur1);
	            vect1.push_back(cur2);
        	}
        	else
        	{
        		std::string cur5 = "";
	            cur5.append(vect[i]);
	            cur5.append(a);
	            
	            vect1.push_back(cur5);
        	}
            
        }
        else
        {
        	if(n%2==1)
        	{
	        	std::string cur3 = "";
	            cur3.append(vect[i]);
	            cur3.append(b);
	
	            std::string cur4 = "";
	            cur4.append(vect[i]);
	            cur4.append(c);
	
	
	            vect1.push_back(cur3);
	            vect1.push_back(cur4);
        	}
        	else
        	{
        		std::string cur6 = "";
	            cur6.append(vect[i]);
	            cur6.append(a);
	
	            std::string cur7 = "";
	            cur7.append(vect[i]);
	            cur7.append(d);
	            
	            std::string cur8 = "";
	            cur8.append(vect[i]);
	            cur8.append(c);
	            
	            vect1.push_back(cur6);
	            vect1.push_back(cur7);
	            vect1.push_back(cur8);
        	}
            

        }
        if(i==sum_clen-1)
        {
        	if(n%2==1) // для четн и нечетн считаем отдельно
        	{
        		ptr_len+=2;//смещаем индекс посл элемента на 2
                sum_clen = z_len * 3 + o_len * 2; // общая сумма элементов после итераций равна
                o_len = z_len + o_len; //эл тов на 1 равно
                z_len = sum_clen - o_len; //эл тов на 0 - все - на 1
             	i = -1;
        	    cur_len+=2; // grade current length on 2
        	}
        	else
        	{
        		ptr_len+=2;
                sum_clen = z_len  + o_len * 3; 
                o_len = o_len*2;
                z_len = sum_clen - o_len;
             	i = -1;
        	    cur_len+=2;
        	}
        
        
 
  		
       		while (!vect.empty())
       		{
       			vect.pop_back();
       		}
       		
       		#pragma omp paralel for shedule(guided,4)
            for (int j = 0; j < sum_clen; j++)
            {
                vect.push_back(vect1[j]);
            }
            
				while (!vect1.empty())
       	    {
       			vect1.pop_back();
       		}
        }


    }
    
   
    std::cout << "Here is smth that u'll sooooo like : " << std::endl;
    
	std::ofstream file("generations.txt");
	
    #pragma omp paralel for shedule(guided,4)
	for (int i = 0; i < vect.size(); i++)
    	{
    		file << vect[i] << std::endl;
    	}
file << vect.size() << std::endl;
file.close();
std::cout << "Goddamn, here is " << vect.size() << " corteges ^^";

}

void ran_algorithm(int n,int ptr_len, int cur_len)
{
	int samp;
	
	srand(time(NULL));
	std::vector <std::string> vect;
	std::vector <std::string> vect1;
	int sum_clen = 1;
	
	if(n%2==0)
	{
	int p0 = rand()%3;
	if (p0==0) vect.push_back("00"); //00
    if (p0==1) vect.push_back("01"); //01
    if (p0==2) vect.push_back("11"); //01
    
	}
	else
	{
	int p00 = rand()%4;
	if (p00==0) vect.push_back("000"); //000
    if (p00==1) vect.push_back("010"); //010
    if (p00==2) vect.push_back("011"); //010
    if (p00==3) vect.push_back("111"); //111
	}
	
const std::string a = "00", b = "10", c = "11", d = "01";

	for (int i = 0; i < sum_clen; i++)
    {

    	
	    if(cur_len >= n) break; 
        if(((int)vect[i][ptr_len]) == 48) //if last el is zero
        {
        	if(n%2==1)
        	{
        		int p = rand()%3;
        		
	        	std::string cur = "";
	            cur.append(vect[i]);
	            cur.append(a);
	
	            std::string cur1 = "";
	            cur1.append(vect[i]);
	            cur1.append(b);
	
	            std::string cur2 = "";
	            cur2.append(vect[i]);
	            cur2.append(c);
	            
				if(p==0) vect1.push_back(cur);
	            if(p==1) vect1.push_back(cur1);
	            if(p==2) vect1.push_back(cur2);
        	}
        	else
        	{
        		std::string cur5 = "";
	            cur5.append(vect[i]);
	            cur5.append(a);
	            
	            vect1.push_back(cur5);
        	}
            
        }
        else
        {
        	if(n%2==1)
        	{
        		int p1 = rand()%2;
	        	std::string cur3 = "";
	            cur3.append(vect[i]);
	            cur3.append(b);
	
	            std::string cur4 = "";
	            cur4.append(vect[i]);
	            cur4.append(c);
	
	
	            if (p1==0) vect1.push_back(cur3);
	            if (p1==1) vect1.push_back(cur4);
        	}
        	else
        	{
        		int p2 = rand()%3;
        		std::string cur6 = "";
	            cur6.append(vect[i]);
	            cur6.append(a);
	
	            std::string cur7 = "";
	            cur7.append(vect[i]);
	            cur7.append(d);
	            
	            std::string cur8 = "";
	            cur8.append(vect[i]);
	            cur8.append(c);
	            
	            if (p2==0) vect1.push_back(cur6);
	            if (p2==1) vect1.push_back(cur7);
	            if (p2==2) vect1.push_back(cur8);
        	}
            

        }
        
        	if(n%2==1) // для четн и нечетн считаем отдельно
        	{
        		ptr_len+=2;//смещаем индекс посл элемента на 2
             	i = -1;
        	    cur_len+=2; // grade current length on 2
        	}
        	else
        	{
        		ptr_len+=2;
             	i = -1;
        	    cur_len+=2;
        	}
        
        
 
  		
       		while (!vect.empty())
       		{
       			vect.pop_back();
       		}
       		
       		#pragma omp paralel for shedule(guided,4)
            for (int j = 0; j < sum_clen; j++)
            {
                vect.push_back(vect1[j]);
            }
            
				while (!vect1.empty())
       	    {
       			vect1.pop_back();
       		}
        }

	std::cout << vect.back();
	
}
