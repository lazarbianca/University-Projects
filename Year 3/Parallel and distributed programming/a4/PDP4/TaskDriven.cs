using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace PDP4
{
    public static class TaskDriven
    {
        public static async Task Run()
        {
            var entry = Dns.GetHostEntry(State.Host);
            var socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
            var endpoint = new IPEndPoint(entry.AddressList[0], State.Port);
            var state = new State(socket);

            await ConnectAsync(state, endpoint);

            await SendAsync(state);

            await ReceiveAsync(state);

            state.Socket.Close();
        }

        private static Task ConnectAsync(State state, IPEndPoint endpoint)
        {
            var tcs = new TaskCompletionSource<bool>();
            state.Socket.BeginConnect(endpoint, ar =>
            {
                try
                {
                    state.Socket.EndConnect(ar);
                    tcs.SetResult(true);
                }
                catch (Exception ex)
                {
                    tcs.SetException(ex);
                }
            }, null);
            return tcs.Task;
        }

        private static Task SendAsync(State state)
        {
            var tcs = new TaskCompletionSource<bool>();
            var requestText = $"GET /documente-utile/ HTTP/1.1\r\nHost: {State.Host}\r\n\r\n";
            var requestBytes = Encoding.UTF8.GetBytes(requestText);
            state.Socket.BeginSend(requestBytes, 0, requestBytes.Length, SocketFlags.None, ar =>
            {
                try
                {
                    state.Socket.EndSend(ar);
                    tcs.SetResult(true);
                }
                catch (Exception ex)
                {
                    tcs.SetException(ex);
                }
            }, null);
            return tcs.Task;
        }

        private static Task ReceiveAsync(State state)
        {
            var tcs = new TaskCompletionSource<bool>();
            state.Socket.BeginReceive(state.Buffer, 0, State.BufferLength, SocketFlags.None, ar =>
            {
                try
                {
                    var bytesReceived = state.Socket.EndReceive(ar);
                    if (bytesReceived == 0)
                    {
                        Console.WriteLine(state.Content.ToString());
                        tcs.SetResult(true);
                    }
                    else
                    {
                        var responseText = Encoding.UTF8.GetString(state.Buffer, 0, bytesReceived);
                        state.Content.Append(responseText);
                        state.Socket.BeginReceive(state.Buffer, 0, State.BufferLength, SocketFlags.None, ar2 =>
                        {
                            Console.WriteLine("Reading buffer");
                            ReceiveAsync(state);
                        }, null);
                    }
                }
                catch (Exception ex)
                {
                    tcs.SetException(ex);
                }
            }, null);
            return tcs.Task;
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