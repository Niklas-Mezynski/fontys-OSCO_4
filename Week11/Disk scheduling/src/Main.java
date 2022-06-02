public class Main {

    public static Integer[] trackRequests = {55, 58, 39, 18, 90, 160, 150, 38, 184};

    public static void main(String[] args) {
        //Create the disks
        FIFODisk fifoDisk = new FIFODisk();
        ShortestServiceTimeNextDisk shortestServiceTimeNextDisk = new ShortestServiceTimeNextDisk();
        ScanElevatorDisk scanElevatorDisk = new ScanElevatorDisk();
        CircularScanDisk circularScanDisk = new CircularScanDisk();

        //Run the simulations
        int fifoRuntime = fifoDisk.startSimulation();
        int shortestServiceTimeNextRuntime = shortestServiceTimeNextDisk.startSimulation();
        int scanElevatorSimulation = scanElevatorDisk.startSimulation();
        int circularScanSimulation = circularScanDisk.startSimulation();

        //Print all the results
        System.out.printf("FIFO runtime: %d%n", fifoRuntime);
        System.out.printf("ShortestServiceTimeNext runtime: %d%n", shortestServiceTimeNextRuntime);
        System.out.printf("ScanElevator runtime: %d%n", scanElevatorSimulation);
        System.out.printf("CircularScan runtime: %d%n", circularScanSimulation);
    }
}
