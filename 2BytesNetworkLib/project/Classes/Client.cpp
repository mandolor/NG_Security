#include <Client.h>
#include <cstdlib>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

void Client::create_session(std::string ip_address, std::string port,
                            const char* data, boost::function<void(char*)> onReceive)
{
    boost::asio::io_service io_service;
    
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(ip_address, port);
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
    
    boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
    ctx.load_verify_file("rootca.crt");
    
    Client client(io_service, ctx, iterator);
    client.m_receive_callback = onReceive;
    std::copy(data, data + max_length, client.m_request);
    
    io_service.run();
}

Client::Client(boost::asio::io_service& io_service,
           boost::asio::ssl::context& context,
           boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : m_socket(io_service, context)
{
    m_socket.set_verify_mode(boost::asio::ssl::verify_peer);
    m_socket.set_verify_callback(boost::bind(&Client::verify_certificate, this, _1, _2));

    boost::asio::async_connect(m_socket.lowest_layer(), endpoint_iterator,
                               boost::bind(&Client::handle_connect, this,
                                           boost::asio::placeholders::error));
}

bool Client::verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
{
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.
    
    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";
    
    return preverified;
}

void Client::handle_connect(const boost::system::error_code& error)
{
    if (!error)
    {
        m_socket.async_handshake(boost::asio::ssl::stream_base::client,
                                boost::bind(&Client::handle_handshake, this,
                                            boost::asio::placeholders::error));
    }
    else
    {
        std::cout << "Connect failed: " << error.message() << "\n";
    }
}

void Client::handle_handshake(const boost::system::error_code& error)
{
    if (!error)
    {
        size_t request_length = strlen(m_request);
        
        boost::asio::async_write(m_socket,
                                 boost::asio::buffer(m_request, request_length),
                                 boost::bind(&Client::handle_write, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "Handshake failed: " << error.message() << "\n";
    }
}

void Client::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        boost::asio::async_read(m_socket,
                                boost::asio::buffer(m_response, bytes_transferred),
                                boost::bind(&Client::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "Write failed: " << error.message() << "\n";
    }
}

void Client::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
		m_receive_callback(&m_response[0]);
    }
    else
    {
        std::cout << "Read failed: " << error.message() << "\n";
    }
}
