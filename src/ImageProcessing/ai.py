import cv2
import numpy as np
import serial
import time

# Setting up the serial connection
ser = serial.Serial("COM5", 9600, timeout=1.0)  # Replace "COM5" with the appropriate port
time.sleep(3)  # Delay to allow the connection to open
ser.reset_input_buffer()  # Reset the input buffer
print("Serial OK")  # Confirm serial connection is established

# Function for color detection using Gaussian Blur and inRange technique
def detect_color(image, lower_bound, upper_bound):
    blurred = cv2.GaussianBlur(
        image, (15, 15), 0
    )  # Reducing noise using Gaussian Blur
    mask = cv2.inRange(blurred, lower_bound, upper_bound)  # Creating a mask for the specified color
    return mask

# Setting HSV color bounds for red and green
lower_red = np.array([0, 100, 100])
upper_red = np.array([10, 255, 255])

lower_green = np.array([35, 50, 50])
upper_green = np.array([85, 255, 255])

try:
    cap = cv2.VideoCapture(1)  # Open the camera
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 3840)  # Set 4K resolution width
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 2160)  # Set 4K resolution height
    cap.set(cv2.CAP_PROP_BRIGHTNESS, 150)
    cap.set(cv2.CAP_PROP_CONTRAST, 50)
    cap.set(cv2.CAP_PROP_SATURATION, 50)

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to capture frame")
            break

        frame = cv2.flip(frame, 1)  # Flip the frame horizontally

        # Cropping the frame's sides
        height, width, _ = frame.shape
        left_margin = int(width * 0.1)
        right_margin = int(width * 0.1)
        frame = frame[:, left_margin : width - right_margin]

        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)  # Convert the frame to HSV color space
        # Detect colors
        red_mask = detect_color(hsv, lower_red, upper_red)
        green_mask = detect_color(hsv, lower_green, upper_green)

        # Count the number of pixels
        red_pixels = np.sum(red_mask > 0)
        green_pixels = np.sum(green_mask > 0)

        # Variable to track if any green or red area is found
        found = False

        # Red color detection
        if red_pixels > 30000:
            x, y, w, h = cv2.boundingRect(red_mask)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)  # Draw red rectangle

            M = cv2.moments(red_mask)
            red_cx = int(M["m10"] / M["m00"])
            if red_cx < width // 6:
                red_position = "Left"
            elif red_cx > 2 * width // 6:
                red_position = "Right"
            else:
                red_position = "Center"

            text = f"Red: {red_position}"
            cv2.putText(
                frame, text, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2
            )
            found = True

            # Send data via serial
            ser.write(f"\nRed {red_position}".encode())

        # Green color detection
        if green_pixels > 30000:
            x, y, w, h = cv2.boundingRect(green_mask)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)  # Draw green rectangle

            M = cv2.moments(green_mask)
            green_cx = int(M["m10"] / M["m00"])
            if green_cx < width // 6:
                green_position = "Left"
            elif green_cx > 2 * width // 6:
                green_position = "Right"
            else:
                green_position = "Center"

            text = f"\nGreen: {green_position}"
            cv2.putText(
                frame, text, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2
            )
            found = True

            # Send data via serial
            ser.write(f"\nGreen {green_position}".encode())

        # If no green or red area is found, display "nothing"
        if not found:
            cv2.putText(
                frame,
                "nothing",
                (50, 50),
                cv2.FONT_HERSHEY_SIMPLEX,
                2,
                (255, 255, 255),
                2,
            )
            # Send data via serial
            ser.write(b"\nNothing")

        # Display the frame and handle exit condition
        cv2.imshow("Detected Green and Red Areas", frame)
        cv2.resizeWindow(
            "Detected Green and Red Areas", 1600, 960
        )  # Resize the window to fit the frame size

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()
    ser.close()  # Close the serial connection

except KeyboardInterrupt:
    print("Serial communication closed")
    ser.close()  # Close the serial connection
