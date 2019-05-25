import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Task
{
    public int taskID;
    public float CPUrequest;
    public float memoryRequest;
    public boolean isItAssigned=false;
    public int probid;

    public Task(int taskID, float CPUrequest, float memoryRequest, int probid)
    {
        this.taskID=taskID;
        this.CPUrequest=CPUrequest;
        this.memoryRequest=memoryRequest;
        this.isItAssigned=false;
        this.probid=probid;
    }

    public Task(Task t)
    {
        this.taskID=t.taskID;
        this.CPUrequest=t.CPUrequest;
        this.memoryRequest=t.memoryRequest;
        this.isItAssigned=t.isItAssigned;
        this.probid=t.probid;
    }


    public  float getCPU()
    {
        return CPUrequest;
    }
    public  float getMemory()
    {
        return memoryRequest;
    }



    public static boolean ContainsTask(ArrayList<Task> tasks, Task task)
    {
        boolean contains=false;

        for(int i=0; i<tasks.size();i++)
        {
            if(tasks.get(i).taskID==task.taskID)
            {
                contains=true;
                break;
            }
        }
        return contains;
    }

    public static ArrayList<Task> TaskSorter(ArrayList<Task> tasks, String type, String typeOfOrder)
    {
        ArrayList<Task> ret=new ArrayList<>();

        for(int i=0; i<tasks.size(); i++)
        {
            Task t=new Task(tasks.get(i));
            ret.add(t);
        }
        if(type.equals("All"))
        {
            Collections.sort(ret, new Comparator<Task>()
            {
                @Override public int compare(Task p1, Task p2)
                {
                    return (int)((p1.CPUrequest*p1.memoryRequest) - (p2.CPUrequest*p2.memoryRequest)); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Task::getCPU)); //smallest to largest
        }


        if(type.equals("CPU"))
        {
            Collections.sort(ret, new Comparator<Task>()
            {
                @Override public int compare(Task p1, Task p2)
                {
                    return (int)(p1.CPUrequest - p2.CPUrequest); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Task::getCPU)); //smallest to largest
        }

        if(type.equals("Memory"))
        {
            Collections.sort(ret, new Comparator<Task>()
            {
                @Override public int compare(Task p1, Task p2)
                {
                    return (int)(p1.memoryRequest - p2.memoryRequest); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Task::getMemory)); //smallest to largest
        }

        if(typeOfOrder.equals("decreasing"))
        {
            Collections.reverse(ret);
        }
        return ret;
    }

    public static ArrayList<Task> newTaskSorter(ArrayList<Task> tasks, String type, String typeOfOrder)
    {
        ArrayList<Task> ret=new ArrayList<>();

        int mid=tasks.size()/2;
        int last=tasks.size()-1;
        if(type.equals("largesmall"))
        {
            for (int i = 0; i < mid; i++)
            {
                Task tb = new Task(tasks.get(i));
                ret.add(tb);

                Task te = new Task(tasks.get(last-i));
                ret.add(te);
            }
        }

        if(typeOfOrder.equals("increasing"))
        {
            Collections.reverse(ret);
        }

        return ret;
    }
}