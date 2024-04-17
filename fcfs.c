#include <stdio.h>

int main()
{
    int process_id[15], burst_time[15], n, arrival_time[15], total=0, completion_time[15], waiting_time[15];

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    printf("Enter process id of all the processes: ");
    for(int i=0;i<n;i++)
        {scanf("%d",&process_id[i]);}

    printf("Enter burst time of all the processes: ");
    for(int i=0;i<n;i++)
        {scanf("%d",&burst_time[i]);}

    printf("Enter arrival_timeival time of all the processes: ");
    for(int i=0;i<n;i++)
        {scanf("%d",&arrival_time[i]);}

    int i;
    waiting_time[0]=0;


    //Sort processes based on arrival time
    for (i=0; i<n; i++)
        {
            for(int j=0; j<n-1; j++)
                {
                    if(arrival_time[j]>arrival_time[j+1])
                        {
                            int temp=arrival_time[j];
                            arrival_time[j]=arrival_time[j+1];
                            arrival_time[j+1]=temp;

                            temp=burst_time[j];
                            burst_time[j]=burst_time[j+1];
                            burst_time[j+1]=temp;

                            temp=process_id[j];
                            process_id[j]=process_id[j+1];
                            process_id[j+1]=temp;
                        }
                }
        }

    //for calculating completion time of each process
    completion_time[0]=arrival_time[0]+burst_time[0];
    for(i=1; i<n; i++)
        {
            int temp=0;
            if(arrival_time[i]>completion_time[i-1])                        //if next process arrives way after completion of current process 
                {temp=arrival_time[i]-completion_time[i-1];}
            completion_time[i]=completion_time[i-1]+burst_time[i]+temp;
        }

    //for calculating waiting time of each process
    for(i=1; i<n; i++)
        {waiting_time[i]= completion_time[i]-arrival_time[i]-burst_time[i];}

    //re-sort the processes according to their process id
    for (i=0; i<n; i++)
        {
            for(int j=0; j<n-1; j++)
                {
                    if(process_id[j]>process_id[j+1])
                        {
                            int temp=arrival_time[j];
                            arrival_time[j]=arrival_time[j+1];
                            arrival_time[j+1]=temp;

                            temp=burst_time[j];
                            burst_time[j]=burst_time[j+1];
                            burst_time[j+1]=temp;

                            temp=process_id[j];
                            process_id[j]=process_id[j+1];
                            process_id[j+1]=temp;

                            temp=completion_time[j];
                            completion_time[j]=completion_time[j+1];
                            completion_time[j+1]=temp;

                            temp=waiting_time[j];
                            waiting_time[j]=waiting_time[j+1];
                            waiting_time[j+1]=temp;
                        }
                }
        }


    printf("Process ID     arrival_timeival Time    Burst Time     Waiting Time     TurnAround Time\n");
    float total_waiting_time=0.0;
    float total_turnaround_time= 0.0;
    for(i=0; i<n; i++)
    {
        printf("%d\t\t", process_id[i]);
        printf("%d\t\t", arrival_time[i]);
        printf("%d\t\t", burst_time[i]);
        printf("%d\t\t", waiting_time[i]);
        //calculating and printing turnaround time of each process
        printf("%d\t\t", burst_time[i]+waiting_time[i]);
        printf("\n");
        //for calculating total waiting time
        total_waiting_time += waiting_time[i];
        //for calculating total turnaround time
        total_turnaround_time += (waiting_time[i]+burst_time[i]);
    }
    float avg_turnaround_time,avg_waiting_time;
    //for calculating average waiting time
    avg_waiting_time = total_waiting_time/n;
    //for calculating average turnaround time
    avg_turnaround_time = total_turnaround_time/n;
    printf("Avg. waiting time= %f\n",avg_waiting_time);
    printf("Avg. turnaround time= %f",avg_turnaround_time);
}