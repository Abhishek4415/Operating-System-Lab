import java.util.Scanner;

public class RoundRobin {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n, timeSlice;
        int[] bt = new int[10];   // Burst Time
        int[] tempBt = new int[10]; // Copy of Burst Time
        int[] wt = new int[10];   // Waiting Time
        int[] tat = new int[10];  // Turnaround Time

        boolean[] finished = new boolean[10];

        double totalWT = 0, totalTAT = 0;
        int time = 0;

        System.out.print("Enter number of processes: ");
        n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            System.out.print("Enter Burst Time for Process " + (i + 1) + ": ");
            bt[i] = sc.nextInt();
            tempBt[i] = bt[i];
            finished[i] = false;
        }

        System.out.print("Enter Time Slice (Quantum): ");
        timeSlice = sc.nextInt();

        int remaining = n;

        // Round Robin execution
        while (remaining > 0) {
            for (int i = 0; i < n; i++) {

                if (!finished[i]) {

                    if (bt[i] <= timeSlice) {
                        time += bt[i];
                        tat[i] = time;
                        bt[i] = 0;
                        finished[i] = true;
                        remaining--;
                    } else {
                        bt[i] -= timeSlice;
                        time += timeSlice;
                    }
                }
            }
        }

        // Calculate WT and TAT totals
        for (int i = 0; i < n; i++) {
            wt[i] = tat[i] - tempBt[i];
            totalWT += wt[i];
            totalTAT += tat[i];
        }

        System.out.println("\nPROCESS\tBT\tWT\tTAT");
        for (int i = 0; i < n; i++) {
            System.out.println((i + 1) + "\t" + tempBt[i] + "\t" + wt[i] + "\t" + tat[i]);
        }

        System.out.printf("\nAverage Waiting Time = %.2f", (totalWT / n));
        System.out.printf("\nAverage Turnaround Time = %.2f\n", (totalTAT / n));

        sc.close();
    }
}
