import http.server
import socketserver
import socket

PORT = 9001
WATER_THRESHOLD = 15.0
TEMPERATURE_THRESHOLD = 27


def replace_images_in_html_file(flower_file_name: str, temperature_file_name: str):
    """
    replacing the flower and the temperature images with the
    :param flower_file_name: the file name of the flower image you want to preview (thirsty_flower, happy_flower...)
    :param temperature_file_name: the file name of the temperature image you want to preview (hot temperature, cold temperature...)
    """
    with open('html_source_file.txt', 'r') as html_file:
        file_source = html_file.read()

        replace_string = file_source.replace('flower_file_name', f'{flower_file_name}.png')
        replace_string = replace_string.replace('temperature_file_name', f'{temperature_file_name}.png')

    with open('../index.html', 'w') as html_file:
        html_file.write(replace_string)


class MyHttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        if self.path.startswith('/?'):
            path = self.path[2:].split('&')

            print('path:', self.path)

            parameters = {parameter.split('=')[0]: parameter.split('=')[1] for parameter in path}

            if 'fhumidity' in parameters and 'ftemperature' in parameters:
                water_amount = float(parameters['fhumidity'])
                temperature_value = float(parameters['ftemperature'])

                if water_amount > WATER_THRESHOLD:
                    flower_state = 'happy_flower'
                else:
                    flower_state = 'thirsty_flower'

                if temperature_value > TEMPERATURE_THRESHOLD:
                    temperature_state = 'hot_temperature'
                else:
                    temperature_state = 'cold_temperature'

                replace_images_in_html_file(flower_state, temperature_state)


hostname = socket.gethostname()

ip_address = socket.gethostbyname(hostname)

print(f"IP Address: {ip_address}, (this address should be entered in the webDashboardServer field in webDashboardUpdater.h )")

Handler = MyHttpRequestHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("Http Server Serving at port", PORT)
    httpd.serve_forever()
