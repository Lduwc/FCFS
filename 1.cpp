#include<iostream>
#include<stdlib.h>
using namespace std;
class Process{
    int id, bt, at, ct, tat, wt;
    public:
    void input(Process*,int );
    void calc(Process *,int);
    void show(Process*,int);
    void sort(Process *, int);
};
int main(){
    int n;
    cout<<"\nNhap so tien trinh: \n";
    cin>>n;
    Process *p = new Process[n];
    Process f;
    f.input(p,n);
    f.sort(p, n);
    f.calc(p,n);
    f.show(p,n);
    return 0;
}
//Nhập arr và burst time
void Process::input(Process *p,int n){
    for(int i = 0;i<n;i++){
        cout<<"\nNhap arrival time cho tien trinh: "<<i+1<<":\n";
        cin>>p[i].at;
        cout<<"\nNhap burst time cho tien trinh: "<<i+1<<":\n";
        cin>>p[i].bt;
        p[i].id = i+1;
    }
}
//tính complete,turn around,waiting
void Process::calc(Process*p, int n){
    int sum = 0;
    sum = sum + p[0].at;
    for(int i = 0;i<n;i++){
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;  
        if(sum<p[i+1].at){
            int t = p[i+1].at-sum;
            sum = sum+t;
        } 
    }
}
//sắp xếp 
void Process::sort(Process*p, int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                int temp;
                //sắp xếp burst times
                temp = p[j].bt;
                p[j].bt = p[j+1].bt;
                p[j+1].bt = temp;
                //sắp xếp arrival times
                temp = p[j].at;
                p[j].at = p[j+1].at;
                p[j+1].at = temp;
                //sắp xếp id tương ứng
                temp = p[j].id;
                p[j].id = p[j+1].id;
                p[j+1].id = temp;
            }
        }
    }
}
//hiện thị
void Process::show(Process*p, int n){
    cout<<"PID\tArrival\tBurst\tWaiting\tTurn Around\tCompletion\n";
    float avg_wt = 0, avg_tat = 0;
    for(int i =0;i<n;i++){
        cout<<"  P["<<p[i].id<<"]\t  "<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].wt<<"\t   "<<p[i].tat<<"\t\t"<<p[i].ct<<"\n";
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    avg_wt /= n;
    avg_tat /= n;
    cout<<"\nThoi gian cho trung binh: "<<avg_wt<<"\n";
    cout<<"Thoi gian hoan thanh trung binh: "<<avg_tat<<"\n";
}