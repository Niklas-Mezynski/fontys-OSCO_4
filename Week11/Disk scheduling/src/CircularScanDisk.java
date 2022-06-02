import java.util.Optional;

public class CircularScanDisk extends Disk {
    @Override
    public int startSimulation() {
        int timeNeeded = 0;
        while (!requests.isEmpty()) {
            timeNeeded++;

            if (currentTrack < min)
                currentTrack = max;

            //If the queue contains a request for the current track -> read data
            if (requests.contains(currentTrack)) {
                requests.removeFirstOccurrence(currentTrack);

                //Check if moving direction needs to be changed
                boolean keepDirection = requests.stream()
                        .anyMatch((request) -> request < currentTrack);

                //Skip to the top again (and change the time)
                if (!keepDirection) {
                    Optional<Integer> max = requests.stream().max(Integer::compare);
                    if (max.isPresent()) {
                        timeNeeded += max.get() - currentTrack;
                        currentTrack = max.get();
                    }
                }
                continue;
            }

            //Move to proper direction
            currentTrack--;
        }
        return timeNeeded;
    }
}
