import cv2
import controller as cnt
from cvzone.HandTrackingModule import HandDetector

detector = HandDetector(detectionCon=0.6) #, maxHands=1)
video = cv2.VideoCapture(0)

while True:
    ret, frame = video.read()
    #frame = cv2.flip(frame, 1)
    hands, img = detector.findHands(frame)
    if hands:
        lmList = hands[0]
        fingerUp = detector.fingersUp(lmList)

        print(fingerUp)
        cnt.led(fingerUp)

        finger_sum = sum(fingerUp)
        cv2.putText(frame, f'finger count: {finger_sum}', (2, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 255), 1, cv2.LINE_AA)

    cv2.imshow("frame", frame)
    q = cv2.waitKey(1)
    if q == ord("q"):
        break

video.release()
cv2.destroyAllWindows()
