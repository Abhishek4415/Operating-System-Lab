import java.util.Scanner;

public class SJF {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int[] process = new int[20];
        int[] bt = new int[20];
        int[] wt = new int[20];
        int[] tat = new int[20];

        int n;
        float wtavg = 0, tatavg = 0;

        System.out.print("Enter number of processes: ");
        n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            process[i] = i;
            System.out.print("Enter Burst Time for Process " + i + ": ");
            bt[i] = sc.nextInt();
        }

        // Sorting processes by burst time using Bubble Sort
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (bt[i] > bt[j]) {
                    int temp = bt[i];
                    bt[i] = bt[j];
                    bt[j] = temp;

                    temp = process[i];
                    process[i] = process[j];
                    process[j] = temp;
                }
            }
        }

        wt[0] = 0;
        tat[0] = bt[0];
        tatavg = tat[0];

        for (int i = 1; i < n; i++) {
            wt[i] = wt[i - 1] + bt[i - 1];
            tat[i] = wt[i] + bt[i];

            wtavg += wt[i];
            tatavg += tat[i];
        }

        System.out.println("\nPROCESS\tBT\tWT\tTAT");
        for (int i = 0; i < n; i++) {
            System.out.println("P" + process[i] + "\t" + bt[i] + "\t" + wt[i] + "\t" + tat[i]);
        }

        System.out.println("\nAverage Waiting Time = " + (wtavg / n));
        System.out.println("Average Turnaround Time = " + (tatavg / n));

        sc.close();
    }
}
