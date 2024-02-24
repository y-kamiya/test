use std::io::prelude::*;
use std::net::TcpStream;
use std::net::TcpListener;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    for stream in listener.incoming() {
        let _stream = stream.unwrap();
        println!("connection established");
        handle_connection(_stream);
    }
}

fn handle_connection(mut stream: TcpStream) {
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();

    let request = String::from_utf8_lossy(&buffer[..]);
    println!("request: {}", request);

    let response = format!("HTTP/1.1 200 OK\r\n\r\nyour request is\r\n---\r\n{}", request);
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}
