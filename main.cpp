#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost("voidrealms.com",80);
    qInfo() << "Connecting...";
    if(socket.waitForConnected(60000))
    {
        qInfo() << "Connected sending request";

        QByteArray data;
        data.append("GET /get HTTP/1.1\r\n");
        data.append("Host: local\r\n");
        data.append("Connection: Close\r\n");
        data.append("\r\n");

        socket.write(data);
        socket.waitForBytesWritten();

        if(socket.waitForReadyRead(60000))
        {
            QByteArray response = socket.readAll();
            qInfo() << "Response: " << response.length() << "bytes";
            qInfo() << "Response: " << response;
        }

        //socket.close(); //we asked the server to close the connection
        socket.waitForDisconnected();
        qInfo() << "Done!";

    }
    else
    {
        qInfo() << socket.errorString();
    }

    return a.exec();
}
