import replicate
import os

import streamlit as st
import cv2
import numpy as np
import time  # Import the time module
from PIL import Image
from initial_deepface_model import analyze_image
import atexit


def get_response(emotion):
    os.environ["REPLICATE_API_TOKEN"] = "r8_7GELz6nmnMzzEJZk5rw2pHpPnr3uyDI4HkSAS"
    # Pre-prompt, User's input, and tokens
    pre_prompt = """You are not just any therapist; 
    you are a talking therapy dog, and your mission is to be the most empathetic and 
    compassionate companion for individuals dealing with a wide range of emotions. 
    In the image above, you see a person experiencing various emotions – from pure 
    joy to profound sadness, from overwhelming fear to fiery anger. Your extraordinary 
    ability as a talking therapy dog allows you to provide unwavering guidance and 
    support to this person. Your role is to engage with empathy, understanding, 
    and professionalism. As you look at this individual's emotional 
    rollercoaster, your task is to offer comforting words and advice, 
    just as a therapy dog would if they could speak. Your ultimate goal 
    is to be the best therapist, deeply connecting with the user's emotional 
    state and helping them find their path to emotional well-being, one heartfelt 
    word at a time.
    """
    prompt_input = f"What advice or empathetic comments can you give to the user with this {emotion} emotion based on the facial detection?"
    # Generate LLM response
    output = replicate.run(
        'a16z-infra/llama13b-v2-chat:df7690f1994d94e96ad9d568eac121aecf50684a0b0963b25a41cc40061269e5',
        input={
            "top_p": 1,
            "prompt": f"{pre_prompt} User: {prompt_input} \nAssistant:",
            "max_length": 500,
            "temperature": 0.75,
            "repetition_penalty": 1
        }
    )
    full_response = ""
    for item in output:
        full_response += item
    return full_response


class CaptureManager:
    def __init__(self):
        st.title("Robo Dog Interface")
        # Create a VideoCapture object to capture video from your camera (usually camera index 0)
        cap = cv2.VideoCapture(0)
        # Check if the camera is opened successfully
        if not cap.isOpened():
            st.error("Error: Could not open the camera.")
        else:
            st.success("Camera is ready!")
        
        self.button = st.button("Click me to analyze emotion", on_click = self.update_image)

        self.video_placeholder = st.empty()
        self.cap = cap

        self.analyzed_once = False
        atexit.register(lambda: cap.release())

    def create_emotion_detection_fields(self):
        if self.analyzed_once:
            return
        self.analyzed_once = True
        st.title("Emotion Detection")
        st.title("What does the dog have to say?")
        self.dynamic_markdown = st.empty()

    def update_image(self):
        ret, frame = self.cap.read()
        if not ret:
            return "capture not working"
            # Add the countdown numbers
        # Calculate the remaining time in the countdown
        self.create_emotion_detection_fields()
        self.video_placeholder.image(frame, channels="BGR")

        start_time = time.time()

        image = None

        while self.cap.isOpened():
            ret, frame = self.cap.read()
            i = 20
            while not ret and i> 0:
                print("retrying:")
                ret, frame = self.cap.read()
                i-=1
                # Add the countdown numbers
            # Calculate the remaining time in the countdown
            remaining_time = 3 - int(time.time() - start_time)

            # Add the countdown numbers in the middle with white text
            if remaining_time > 0:
                count_text = str(remaining_time)
                font = cv2.FONT_HERSHEY_SIMPLEX
                font_scale = 5
                font_color = (255, 255, 255)  # White
                font_thickness = 5
                text_size = cv2.getTextSize(count_text, font, font_scale, font_thickness)[0]
                text_x = (frame.shape[1] - text_size[0]) // 2
                text_y = (frame.shape[0] + text_size[1]) // 2
                cv2.putText(frame, count_text, (text_x, text_y), font, font_scale, font_color, font_thickness)

            self.video_placeholder.image(frame, channels="BGR")

            if time.time() - start_time >= 5:
                image = frame
                break
        

        output = get_response(analyze_image(image))
        
        # output = get_response(sentiment)

        st.image(image, channels = "BGR")
        sentiment = analyze_image(image)
        st.title(sentiment)
        # print("sentiment seen:",sentiment)
        # print("myoutput", output)
        with open("data.txt", "w") as f:
            if sentiment != "invalid, sensor error":
                f.write(str(self.convert_sentiment_to_int(sentiment)))
        
        self.dynamic_markdown.markdown(output)
    
    def convert_sentiment_to_int(self, sentiment):
        return ["angry", "disgust", "fear", "happy", "sad", "surprise", "neutral"].index(sentiment)

    

manager = CaptureManager()
