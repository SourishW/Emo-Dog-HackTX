# data.txt reeives the test 

from flask import Flask, jsonify

app = Flask(__name__)


def readlines():
    # This function reads lines from a file, for example
    # You can add your own logic here
    try:
            # Read lines from the file
            with open('data.txt', "r") as file:
                lines = file.readline()
            return lines

    except Exception as e:
            return jsonify({'error': str(e)}), 500


@app.route('/', methods=['GET'])
def process_integer():
    # Call the readlines function when a GET request is made
    data = readlines()
    return jsonify(int(data)), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)