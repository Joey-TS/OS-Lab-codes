#include <stdio.h>

int main()
{
    int pid[15], bt[15], n, arr[15], total=0, ct[15], wt[15];

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    printf("Enter process id of all the processes: ");
    for(int i=0;i<n;i++)
        {scanf("%d",&pid[i]);}

    printf("Enter burst time of all the processes: ");
    for(int i=0;i<n;i++)
        {scanf("%d",&bt[i]);}

    printf("Enter arrival time of all the processes: ");
    for(int i=0;i<n;i++)
        {scanf("%d",&arr[i]);}

    int i;
    wt[0]=0;

    for (i=0; i<n; i++)
        {
            for(int j=0; j<n-1; j++)
                {
                    if(arr[j]>arr[j+1])
                        {
                            int temp=arr[j];
                            arr[j]=arr[j+1];
                            arr[j+1]=temp;

                            temp=bt[j];
                            bt[j]=bt[j+1];
                            bt[j+1]=temp;

                            temp=pid[j];
                            pid[j]=pid[j+1];
                            pid[j+1]=temp;
                        }
                }
        }

    //for calculating completion time of each process
    ct[0]=arr[0]+bt[0];
    for(i=1; i<n; i++)
        {
            int temp=0;
            if(arr[i]>ct[i-1])
                {temp=arr[i]-ct[i-1];}
            ct[i]=ct[i-1]+bt[i]+temp;
        }

    //for calculating waiting time of each process
    for(i=1; i<n; i++)
        {wt[i]= ct[i]-arr[i]-bt[i];}

    //re-sort the processes according to their process id
    for (i=0; i<n; i++)
        {
            for(int j=0; j<n-1; j++)
                {
                    if(pid[j]>pid[j+1])
                        {
                            int temp=arr[j];
                            arr[j]=arr[j+1];
                            arr[j+1]=temp;

                            temp=bt[j];
                            bt[j]=bt[j+1];
                            bt[j+1]=temp;

                            temp=pid[j];
                            pid[j]=pid[j+1];
                            pid[j+1]=temp;

                            temp=ct[j];
                            ct[j]=ct[j+1];
                            ct[j+1]=temp;

                            temp=wt[j];
                            wt[j]=wt[j+1];
                            wt[j+1]=temp;
                        }
                }
        }


    printf("Process ID     Arrival Time    Burst Time     Waiting Time     TurnAround Time\n");
    float twt=0.0;
    float tat= 0.0;
    for(i=0; i<n; i++)
    {
        printf("%d\t\t", pid[i]);
        printf("%d\t\t", arr[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", wt[i]);
        //calculating and printing turnaround time of each process
        printf("%d\t\t", bt[i]+wt[i]);
        printf("\n");
        //for calculating total waiting time
        twt += wt[i];
        //for calculating total turnaround time
        tat += (wt[i]+bt[i]);
    }
    float att,awt;
    //for calculating average waiting time
    awt = twt/n;
    //for calculating average turnaround time
    att = tat/n;
    printf("Avg. waiting time= %f\n",awt);
    printf("Avg. turnaround time= %f",att);
}