import cv2
import numpy as np
import serial

# Open Serial connection (make sure to specify the correct port)
ser = serial.Serial("COM3", 9600)  # Replace 'COM3' with the appropriate port for you

# Open the camera
cap = cv2.VideoCapture(1)

while True:
    # Read the frame from the camera
    ret, frame = cap.read()

    if not ret:
        break

    # Convert the frame to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Define the range of the green color in HSV color space
    lower_green = np.array([35, 50, 50])
    upper_green = np.array([85, 255, 255])

    # Define the range of the red color in HSV color space
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])

    # Extract only the green pixels
    green_mask = cv2.inRange(hsv, lower_green, upper_green)

    # Extract only the red pixels
    red_mask = cv2.inRange(hsv, lower_red, upper_red)

    # Find contours for the green areas
    green_contours, _ = cv2.findContours(
        green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    # Find contours for the red areas
    red_contours, _ = cv2.findContours(
        red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    # Variable to track if any green or red area is found
    found = False

    # Draw a green rectangle around each green area containing at least 1000 pixels and write "green"
    for contour in green_contours:
        if cv2.contourArea(contour) >= 15000:
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.putText(
                frame,
                "green",
                (x + w + 10, y + 30),
                cv2.FONT_HERSHEY_SIMPLEX,
                1,
                (0, 255, 0),
                2,
            )
            ser.write(b"green\n")  # Send the text over serial
            found = True

    # Draw a red rectangle around each red area containing at least 1000 pixels and write "red"
    for contour in red_contours:
        if cv2.contourArea(contour) >= 15000:
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
            cv2.putText(
                frame,
                "red",
                (x + w + 10, y + 30),
                cv2.FONT_HERSHEY_SIMPLEX,
                1,
                (0, 0, 255),
                2,
            )
            ser.write(b"red\n")  # Send the text over serial
            found = True

    # If no green or red area is found, display the text "nothing"
    if not found:
        cv2.putText(
            frame, "nothing", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (255, 255, 255), 2
        )
        ser.write(b"noth\n")  # Send the text over serial

    # Display the frame
    cv2.imshow("Detected Green and Red Areas", frame)

    # Exit the program when the "q" key is pressed
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# Release the camera and close all windows
cap.release()
cv2.destroyAllWindows()

# Close the serial connection
ser.close()
