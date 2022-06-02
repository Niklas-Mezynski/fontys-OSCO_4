public class ShortestServiceTimeNextDisk extends Disk {
    @Override
    public int startSimulation() {
        int timeNeeded = 0;
        while (!requests.isEmpty()) {
            timeNeeded++;

            //Find shortest dist
            int shortest = findRequestWithMinDist();

            //Check if shortest is reached
            if (currentTrack == shortest) {
                requests.removeFirstOccurrence(shortest);
                continue;
            }

            //Else move to shortest
            if (shortest > currentTrack) {
                currentTrack++;
            } else {
                currentTrack--;
            }
        }
        return timeNeeded;
    }


}
