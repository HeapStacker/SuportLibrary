#include "fileSuport.h"
#include "vectorSuport.h"

//networking...
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE //because we want to only use asio not whole boost
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


vector<char> vBuffer(1 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket) {

    //asio samo čeka u pozadini(nije recursive nightmare) kad na socket dođe data i ako se ne aktivira error code, konzola ispiše datu
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), [&](std::error_code ec, std::size_t length) {
        if (!ec) {
            cout << "\n\nRead " << length << " bytes\n\n";
            for (int i = 0; i < length; i++)
                cout << vBuffer[i];
            GrabSomeData(socket);
        }
    });
}

void helper() {
    asio::error_code ec;
    asio::io_context context; //instanca asia

    //upišemo adresu mjesta gdje se želimo spojiti...
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("31.13.84.8", ec), 80);

    //napravimo socket
    asio::ip::tcp::socket socket(context);

    //kažemo socketu da se proba connectati
    socket.connect(endpoint, ec);

    if (!ec) {
        cout << "Connected\n";
    }
    else {
        cout << "Failed to connect to address: \n" << ec.message() << endl;
    }

    //http req jer se spajamo na port 80
    if (socket.is_open()) {
        GrabSomeData(socket);

        std::string sRequest = 
        "GET /v/t15.5256-10/274974326_452219510021912_3998104448829108642_n.jpg?stp=dst-jpg_p960x960&_nc_cat=104&ccb=1-5&_nc_sid=ad6a45&_nc_eui2=AeHTXGSDSKLVgJOEHJ9GfFcMOJlaSWQz2z84mVpJZDPbPyiOQuvAQ2YsCl0xfN-jdLgvJE3mKDmrb4qFxoHU_9bx&_nc_ohc=3GgnnGvaa_UAX-BaTMs&_nc_oc=AQlHPJSTJJKb-IP0hHlbrJwHtRkWVZb6XTuxhPcLoFe3D5lICdvWEXcbeQ4k93Rqs-I&tn=tIbBbgJr_MDL4nFN&_nc_ht=scontent-frt3-1.xx&oh=00_AT-O8QbCaKCLrLyLCmIMXD3CIPZ0KC6YrGQuBVl0x5KjSw&oe=6257CEA9 undefined\n"
        "Host: scontent-frt3-1.xx.fbcdn.net\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:98.0) Gecko/20100101 Firefox/98.0\n"
        "Accept: image/avif,image/webp,*/*\n"
        "Accept-Language: en-US,en;q=0.5\n"
        "Accept-Encoding: gzip, deflate, br\n"
        "Referer: https://www.facebook.com/\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
    }
}