using PPDLab4;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDP4
{
    internal class Program
    {
        public static void Main()
        {
            //MethodEventDriven();
            MethodTaskDriven();
            //MethodAwaitAsyncDriven();
        }

        private static void MethodEventDriven()
        {
            EventDriven.Run();
        }

        private static void MethodTaskDriven()
        {
            TaskDriven.Run().Wait();
        }

        private static void MethodAwaitAsyncDriven()
        {
            Await_Async.Run().Wait();
        }
    }
}
