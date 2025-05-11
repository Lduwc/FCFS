#include <iostream>
using namespace std;

void queueUpdation(int queue[],int timer,int arrival[],int n, int maxProccessIndex){
    int zeroIndex;
    for(int i = 0; i < n; i++){
        if(queue[i] == 0){
            zeroIndex = i;
            break;
        }
    }   
    queue[zeroIndex] = maxProccessIndex + 1;
}

void queueMaintainence(int queue[], int n){
    for(int i = 0; (i < n-1) && (queue[i+1] != 0) ; i++){
        int temp = queue[i];
        queue[i] = queue[i+1];
        queue[i+1] = temp; 
    }
}

void checkNewArrival(int timer, int arrival[], int n, int maxProccessIndex,int queue[]){
    if(timer <= arrival[n-1]){
       bool newArrival = false;
       for(int j = (maxProccessIndex+1); j < n; j++){
             if(arrival[j] <= timer){
              if(maxProccessIndex < j){
                 maxProccessIndex = j;
                 newArrival = true;
              }
           }
       }
       //thêm quy trình đến vào hàng đợi sẵn sàng
       //(nếu có đến)
       if(newArrival)
          queueUpdation(queue,timer,arrival,n, maxProccessIndex);
    }
}


int main(){
    int n,tq, timer = 0, maxProccessIndex = 0;
    float avgWait = 0, avgTT = 0;
    cout << "\n Nhap Quantum : ";
    cin>>tq;
    cout << "\n Nhap so tien trinh : ";
    cin>>n;
    int arrival[n], burst[n], wait[n], turn[n], queue[n], temp_burst[n];
    bool complete[n];

    cout << "\nNhap arrival time cua tien trinh : ";
    for(int i = 0; i < n; i++)
        cin>>arrival[i];

    cout << "\nNhap burst time cua tien trinh : ";
    for(int i = 0; i < n; i++){
        cin>>burst[i];
        temp_burst[i] = burst[i];
    }

    for(int i = 0; i < n; i++){    //Khởi tạo hàng đợi và mảng
        complete[i] = false;
        queue[i] = 0;
    }
    while(timer < arrival[0])    //Hẹn giờ tăng cho đến khi tiến trình đầu tiên đến
        timer++; 
    queue[0] = 1;
    
    while(true){
        bool flag = true;
        for(int i = 0; i < n; i++){
            if(temp_burst[i] != 0){
                flag = false;
                break;
            }
        }
        if(flag)
            break;

        for(int i = 0; (i < n) && (queue[i] != 0); i++){
            int ctr = 0;
            while((ctr < tq) && (temp_burst[queue[0]-1] > 0)){
                temp_burst[queue[0]-1] -= 1;
                timer += 1;
                ctr++;

                //Kiểm tra và cập nhật hàng đợi sẵn sàng cho đến khi tất cả các tiến trình đến
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
            }
            //Nếu 1 tiến trình hoàn thành, hãy lưu trữ thời gian thoát 
            //và đánh dấu nó như đã hoàn thành
            if((temp_burst[queue[0]-1] == 0) && (complete[queue[0]-1] == false)){
                //turn array hiện lưu trữ thời gian hoàn thành
                turn[queue[0]-1] = timer;        
                complete[queue[0]-1] = true;
            }
            
              //kiểm tra CPU có nhàn rỗi không
            bool idle = true;
            if(queue[n-1] == 0){
                for(int i = 0; i < n && queue[i] != 0; i++){
                    if(complete[queue[i]-1] == false){
                        idle = false;
                    }
                }
            }
            else
                idle = false;

            if(idle){
                timer++;
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
            }
      
            //Duy trì các mục nhập của các tiến trình
            //sau mỗi lần sắp xếp trong hàng đợi sẵn sàng
            queueMaintainence(queue,n);
        }
    }

    for(int i = 0; i < n; i++){
        turn[i] = turn[i] - arrival[i];
        wait[i] = turn[i] - burst[i];
    }

    cout << "\nPID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnAround Time" << endl;
    for(int i = 0; i < n; i++){
        int completionTime = arrival[i] + turn[i] + burst[i];
        cout<<i+1<<"\t\t"<<arrival[i]<<"\t\t"
          <<burst[i]<<"\t\t"<<completionTime << "\t\t"<<wait[i]<<"\t\t"<<turn[i]<<endl;
    }
    for(int i =0; i< n; i++){
        avgWait += wait[i];
        avgTT += turn[i]; 
    }
    cout<<"\nThoi gian cho trung binh: "<<(avgWait/n)
      <<"\nThoi gian hoan thanh trung binh : "<<(avgTT/n);

    return 0;
    
}