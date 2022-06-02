import java.util.LinkedList;

public class FIFODisk extends Disk {

    @Override
    public int startSimulation() {
        int timeNeeded = 0;
        while (!requests.isEmpty()) {
            timeNeeded++;

            //If first request is reached --> remove it
            if (currentTrack == requests.getFirst()) {
                requests.removeFirst();
                continue;
            }

            //Else move to the next track
            if (requests.getFirst() > currentTrack)
                currentTrack++;
            else
                currentTrack--;
        }
        return timeNeeded;
    }
}
