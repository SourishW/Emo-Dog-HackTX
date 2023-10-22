from deepface import DeepFace
import transformers
import cv2
import matplotlib.pyplot as plt


def analyze_image(image):
    img = image
    try:
        result = DeepFace.analyze(img, actions=['emotion'])

    except Exception as e:
        return "neutral"
    emotions = result[0]["emotion"]
    print(emotions)
    maximum_emotion = max(emotions, key=lambda k: emotions[k])
    return maximum_emotion

