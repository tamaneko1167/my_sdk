import socket
 
ip_address = socket.gethostbyname(socket.gethostname())
tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_socket.connect((str(ip_address), 52001))
 
tcp_socket.send('Hello!'.encode("utf-8"))
response = tcp_socket.recv(1024)
print('Data : {}'.format(response.decode("utf-8")))