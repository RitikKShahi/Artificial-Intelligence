import cv2
import mediapipe as mp
import numpy as np
import math
import os
import time

# -------- MediaPipe Config (Optimized) --------
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,  # Track only one hand
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7
)

mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

prev_volume = 0
smoothed_length = 0
alpha = 0.2  # EMA smoothing factor
prev_time = 0

while True:
    success, img = cap.read()
    img = cv2.flip(img, 1)  # Mirror view
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRGB)

    if results.multi_hand_landmarks:
        handLms = results.multi_hand_landmarks[0]

        h, w, _ = img.shape

        x1 = int(handLms.landmark[4].x * w)
        y1 = int(handLms.landmark[4].y * h)
        x2 = int(handLms.landmark[8].x * w)
        y2 = int(handLms.landmark[8].y * h)

        length = math.hypot(x2 - x1, y2 - y1)

        # -------- Smooth Distance (EMA Filter) --------
        smoothed_length = alpha * length + (1 - alpha) * smoothed_length

        # Map to volume
        volume = np.interp(smoothed_length, [30, 220], [0, 100])
        volume = np.clip(volume, 0, 100)

        # Update only if change > 4%
        if abs(volume - prev_volume) > 4:
            os.system(f"osascript -e 'set volume output volume {int(volume)}'")
            prev_volume = volume

        # -------- UI --------
        cv2.circle(img, (x1, y1), 8, (255,0,0), cv2.FILLED)
        cv2.circle(img, (x2, y2), 8, (255,0,0), cv2.FILLED)
        cv2.line(img, (x1, y1), (x2, y2), (0,255,0), 2)

        # Volume Bar
        bar = np.interp(volume, [0,100], [400,150])
        cv2.rectangle(img, (50,150), (85,400), (255,0,0), 2)
        cv2.rectangle(img, (50,int(bar)), (85,400), (255,0,0), cv2.FILLED)

        cv2.putText(img, f'Vol: {int(volume)} %', (40, 440),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255), 2)

        mp_draw.draw_landmarks(img, handLms, mp_hands.HAND_CONNECTIONS)

    # -------- FPS Counter --------
    curr_time = time.time()
    fps = 1 / (curr_time - prev_time) if prev_time else 0
    prev_time = curr_time

    cv2.putText(img, f'FPS: {int(fps)}', (450, 50),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)

    cv2.imshow("Optimized Gesture Volume Control", img)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
