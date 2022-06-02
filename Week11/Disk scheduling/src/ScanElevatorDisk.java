public class ScanElevatorDisk extends Disk {
    @Override
    public int startSimulation() {
        int timeNeeded = 0;
        int movingDirection = findRequestWithMinDist() >= currentTrack ? 1 : -1;
        while (!requests.isEmpty()) {
            timeNeeded++;

            //If the queue contains a request for the current track -> read data
            if (requests.contains(currentTrack)) {
                requests.removeFirstOccurrence(currentTrack);

                //Check if moving direction needs to be changed
                int finalMovingDirection = movingDirection;
                boolean keepDirection = requests.stream()
                        .anyMatch((request) -> (finalMovingDirection == 1) == (request >= currentTrack));
                if (!keepDirection) {
                    movingDirection *= -1;
                }
                continue;
            }

            //Move to proper direction
            currentTrack += movingDirection;
        }
        return timeNeeded;
    }
}
