#!/bin/bash

# Define the paths to the service executables
PROJECT_DIR="build"
SERVICE_REGISTRY="$PROJECT_DIR/service_registry/ServiceRegistry"
CAMERA_SERVICE="$PROJECT_DIR/camera_service/CameraService"
STREAMER_SERVICE="$PROJECT_DIR/streamer_service/StreamerService"
TRACKER_SERVICE="$PROJECT_DIR/tracker_service/TrackerService"
KEYBOARD_INPUT_SERVICE="$PROJECT_DIR/keyboard_input_service/KeyboardInputService"

# Start the ServiceRegistry in a new terminal window
gnome-terminal -- bash -c "$SERVICE_REGISTRY; exec bash"
sleep 1

# Start the CameraService in a new terminal window
gnome-terminal -- bash -c "$CAMERA_SERVICE; exec bash"
sleep 1
# Start the StreamerService in a new terminal window
gnome-terminal -- bash -c "$STREAMER_SERVICE; exec bash"
sleep 1
# Start the TrackerService in a new terminal window
gnome-terminal -- bash -c "$TRACKER_SERVICE; exec bash"
sleep 1
# Start the KeyboardInputService in a new terminal window
gnome-terminal -- bash -c "$KEYBOARD_INPUT_SERVICE; exec bash"

echo "All services started."
