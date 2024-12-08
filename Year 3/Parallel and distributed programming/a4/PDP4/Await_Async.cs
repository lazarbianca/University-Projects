using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace PPDLab4
 {
    public static class Await_Async
    {
        public static async Task Run()
        {
            var entry = Dns.GetHostEntry(State.Host);
            var socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            var endpoint = new IPEndPoint(entry.AddressList[0], State.Port);
            var state = new State(socket);

            await socket.ConnectAsync(endpoint);

            await SendAsync(state);

            await ReceiveAsync(state);

            socket.Close();
        }

        private static async Task SendAsync(State state)
        {
            var requestText = $"GET /documente-utile/ HTTP/1.1\r\nHost: {State.Host}\r\n\r\n";
            var requestBytes = Encoding.UTF8.GetBytes(requestText);
            await state.Socket.SendAsync(new ArraySegment<byte>(requestBytes), SocketFlags.None);
        }

        private static async Task ReceiveAsync(State state)
        {
            var bytesReceived = 0;
            while ((bytesReceived = await state.Socket.ReceiveAsync(new ArraySegment<byte>(state.Buffer), SocketFlags.None)) > 0)
            {
                var responseText = Encoding.UTF8.GetString(state.Buffer, 0, bytesReceived);
                state.Content.Append(responseText);
            }

            Console.WriteLine(state.Content.ToString());
        }

        public sealed class State
        {
            public const string Host = "www.cnatdcu.ro";
            public const int Port = 80;
            public const int BufferLength = 1024;
            public readonly byte[] Buffer = new byte[BufferLength];
            public readonly StringBuilder Content = new StringBuilder();
            public readonly Socket Socket;

            public State(Socket socket)
            {
                Socket = socket;
            }
        }

    }
}
