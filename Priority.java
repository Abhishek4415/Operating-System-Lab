import java.util.Scanner;

public class PriorityScheduling {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int[] process = new int[20];
        int[] bt = new int[20];
        int[] priority = new int[20];
        int[] wt = new int[20];
        int[] tat = new int[20];

        int n;
        float totalWT = 0, totalTAT = 0;

        System.out.print("Enter number of processes: ");
        n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            process[i] = i;
            System.out.print("Enter Burst Time & Priority for Process " + i + ": ");
            bt[i] = sc.nextInt();
            priority[i] = sc.nextInt();
        }

        // Sorting by priority (Lower number = Higher priority)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (priority[i] > priority[j]) {

                    int temp = priority[i];
                    priority[i] = priority[j];
                    priority[j] = temp;

                    temp = bt[i];
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
        totalTAT = tat[0];

        for (int i = 1; i < n; i++) {
            wt[i] = wt[i - 1] + bt[i - 1];
            tat[i] = wt[i] + bt[i];

            totalWT += wt[i];
            totalTAT += tat[i];
        }

        System.out.println("\nPROCESS\tPR\tBT\tWT\tTAT");
        for (int i = 0; i < n; i++) {
            System.out.println("P" + process[i] + "\t" + priority[i] + "\t" + bt[i] + "\t" + wt[i] + "\t" + tat[i]);
        }

        System.out.println("\nAverage Waiting Time = " + (totalWT / n));
        System.out.println("Average Turnaround Time = " + (totalTAT / n));

        sc.close();
    }
}
