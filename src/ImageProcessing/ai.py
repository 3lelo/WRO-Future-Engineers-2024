
import cv2
import numpy as np

# import serial

# فتح اتصال Serial (تأكد من تحديد المنفذ الصحيح)
# ser = serial.Serial("COM3", 9600)  # استبدل 'COM3' بالمنفذ المناسب لديك

# فتح الكاميرا
cap = cv2.VideoCapture(1)

while True:
    # قراءة الإطار من الكاميرا
    ret, frame = cap.read()

    if not ret:
        break

    # تحويل الإطار إلى فضاء الألوان HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # تحديد نطاق اللون الأخضر في فضاء الألوان HSV
    lower_green = np.array([35, 50, 50])
    upper_green = np.array([85, 255, 255])

    # تحديد نطاق اللون الأحمر في فضاء الألوان HSV
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])

    # استخراج البكسلات الخضراء فقط
    green_mask = cv2.inRange(hsv, lower_green, upper_green)

    # استخراج البكسلات الحمراء فقط
    red_mask = cv2.inRange(hsv, lower_red, upper_red)

    # البحث عن الحواف الخارجية للمناطق الخضراء
    green_contours, _ = cv2.findContours(
        green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    # البحث عن الحواف الخارجية للمناطق الحمراء
    red_contours, _ = cv2.findContours(
        red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    # متغير لتتبع إذا تم العثور على أي منطقة خضراء أو حمراء
    found = False

    # رسم مستطيل أخضر حول كل منطقة خضراء تحتوي على 1000 بكسل على الأقل وكتابة "green"
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
            # ser.write(b"green\n")  # إرسال النص عبر السيريل
            found = True

    # رسم مستطيل أحمر حول كل منطقة حمراء تحتوي على 1000 بكسل على الأقل وكتابة "red"
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
            # ser.write(b"red\n")  # إرسال النص عبر السيريل
            found = True

    # إذا لم يتم العثور على أي منطقة خضراء أو حمراء، يعرض النص "noth"
    if not found:
        cv2.putText(
            frame, "nothing", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (255, 255, 255), 2
        )
        # ser.write(b"noth\n")  # إرسال النص عبر السيريل

    # عرض الإطار
    cv2.imshow("Detected Green and Red Areas", frame)

    # إنهاء البرنامج عند الضغط على مفتاح "q"
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# تحرير الكاميرا وإغلاق النوافذ
cap.release()
cv2.destroyAllWindows()

# إغلاق الاتصال بالسيريل
ser.close()
