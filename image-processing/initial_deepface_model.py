from deepface import DeepFace
import transformers
import cv2
import matplotlib.pyplot as plt


def analyze_image(image):
    img = image

    try:
        result = DeepFace.analyze(img, actions=['emotion'])

    except Exception as e:
        return "invalid, sensor error"
    emotions = result[0]["emotion"]
    maximum_value = -1
    max_key = None
    for key, value in emotions.items():
        # if key == "neutral":
        #     continue
        if value>maximum_value:
            maximum_value = value
            max_key = key

    print("Emotions detected:", emotions)
    print("Maximum emotion:", max_key)
        
    return max_key


# print(analyze_image(cv2.imread))

