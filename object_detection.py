import cv2


frameWidth = 200
frameHeight = 100

color = (50, 200, 100)
color2 = (128, 255, 0)

cap = cv2.VideoCapture('test2.mp4')
cap.set(3, frameWidth)
cap.set(4, frameHeight)

cv2.namedWindow('Result')
cv2.resizeWindow('Result', frameWidth, frameHeight + 100)
cv2.createTrackbar('Scale', 'Result', 400, 1000, lambda x: None)
cv2.createTrackbar('Neig', 'Result', 2, 20, lambda x: None)
cv2.createTrackbar('Min Area', 'Result', 0, 100000, lambda x: None)
cv2.createTrackbar('Brightness', 'Result', 180, 255, lambda x: None)

# load classifiers
cascade = cv2.CascadeClassifier('haarcascades/haarcascade_car.xml')
cascade2 = cv2.CascadeClassifier('haarcascades/haarcascade_ped.xml')


def detect_objects(img, cascade):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    scaleVal = 1 + (cv2.getTrackbarPos('Scale', 'Result') / 1000)
    neig = cv2.getTrackbarPos('Neig', 'Result')
    objects = cascade.detectMultiScale(gray, scaleVal, neig)
    minArea = cv2.getTrackbarPos('Min Area', 'Result')
    objects = [(x, y, w, h) for x, y, w, h in objects if w * h > minArea]
    return objects


while True:
    # set cam brightness from trackbar value
    cameraBrightness = cv2.getTrackbarPos('Brightness', 'Result')
    cap.set(10, cameraBrightness)

    # convert image to gray scale
    success, img = cap.read()

    # detect objects
    objects = detect_objects(img, cascade)
    objects2 = detect_objects(img, cascade2)

    # display detected objects
    for x, y, w, h in objects:
        cv2.rectangle(img, (x, y), (x+w, y+h), color, 3)
        roi_color = img[y:y+h, x:x+w]
    for x, y, w, h in objects2:
        cv2.rectangle(img, (x, y), (x+w, y+h), color, 3)
        roi_color = img[y:y+h, x:x+w]

    cv2.putText(img, 'UAV footage', (5, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1, color2, 2)


    cv2.imshow('Result', img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
