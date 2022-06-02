import java.util.Arrays;
import java.util.LinkedList;

public abstract class Disk {
    int currentTrack = 100;
    final int min = 1;
    final int max = 200;
    LinkedList<Integer> requests = new LinkedList<>(Arrays.asList(Main.trackRequests));

    /**
     * @return time needed to process all requests
     */
    public abstract int startSimulation();

    int findRequestWithMinDist() {
        int minValue = Integer.MAX_VALUE;
        int result = 0;
        for (Integer request : requests) {
            if (Math.abs(request - currentTrack) < minValue) {
                minValue = Math.abs(request - currentTrack);
                result = request;
            }
        }
        if (minValue == Integer.MAX_VALUE) {
            throw new RuntimeException("ShortestServiceTimeNextDisk - No min value found");
        }
        return result;
    }
}
