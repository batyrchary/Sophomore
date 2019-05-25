import javax.crypto.Mac;
import java.util.*;
import java.util.concurrent.BlockingDeque;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class Machine
{
    public int myMachineID;
    public float CPU;
    public float Memory;

    public boolean isItOpened=false;
    public String server="";
    public float CPULeft;
    public float MemoryLeft;
    public float totalCapacityLeft;


     public Machine(int mymachineID, float CPU, float Memory, String server)

    {
        this.myMachineID=mymachineID;
        this.CPU=CPU;
        this.Memory=Memory;
        this.isItOpened=false;
        this.server=server;

        this.CPULeft=CPU;
        this.MemoryLeft=Memory;
        this.totalCapacityLeft=CPU*Memory;
    }

    public Machine(Machine m)
    {
        this.myMachineID = m.myMachineID;
        this.CPU = m.CPU;
        this.Memory = m.Memory;
        this.isItOpened = m.isItOpened;
        this.server = m.server;

        this.MemoryLeft = m.MemoryLeft;
        this.CPULeft = m.CPULeft;
        this.totalCapacityLeft=m.totalCapacityLeft;
    }


    public static ArrayList<Machine> CopyMachines(ArrayList<Machine> machines)
    {
        ArrayList<Machine> ret=new ArrayList<>();

        for(int i=0;i <machines.size(); i++)
        {
            Machine m=new Machine(machines.get(i));
            ret.add(m);
        }
        return ret;
    }

    public static int ContainsMachine(ArrayList<Machine> machines, Machine machine)
    {
        int index=-1;

        for(int i=0; i<machines.size();i++)
        {
            if(machines.get(i).myMachineID==machine.myMachineID)
            {
                index=i;
                break;
            }
        }
        return index;
    }


    public float getMemoryLeft() { return MemoryLeft; }

    public float getCPULeft() { return CPULeft; }

    public float getTotalCapacityLeft(){return totalCapacityLeft; }


    public static Machine UpdateMachine(Machine m, Task t)
    {
        Machine mUpdated=new Machine(m);

        mUpdated.MemoryLeft=mUpdated.MemoryLeft-t.memoryRequest;
        mUpdated.CPULeft=mUpdated.CPULeft-t.CPUrequest;
        mUpdated.totalCapacityLeft=mUpdated.totalCapacityLeft-t.CPUrequest*t.memoryRequest;

        mUpdated.isItOpened=true;

        return mUpdated;
    }


    public static ArrayList<Machine> MachineSorter(ArrayList<Machine> machines, String type, String typeOfOrder)
    {
        ArrayList<Machine> ret = new ArrayList<>();

        for(int i=0; i<machines.size(); i++)
        {
            Machine m=new Machine(machines.get(i));
            ret.add(m);
        }


        if(type.equals("All"))
        {
            Collections.sort(ret, new Comparator<Machine>() {
                @Override
                public int compare(Machine p1, Machine p2) {

                    return (int) (p1.totalCapacityLeft - p2.totalCapacityLeft); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Machine::getTotalCapacityLeft)); //smallest to largest
        }
        else if(type.equals("CPU"))
        {
            Collections.sort(ret, new Comparator<Machine>() {
                @Override
                public int compare(Machine p1, Machine p2) {

                    return (int) (p1.CPULeft - p2.CPULeft); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Machine::getTotalCapacityLeft)); //smallest to largest
        }
        else if(type.equals("Memory"))
        {
            Collections.sort(ret, new Comparator<Machine>() {
                @Override
                public int compare(Machine p1, Machine p2) {

                    return (int) (p1.MemoryLeft - p2.MemoryLeft); // Ascending
                }
            });
            ret.sort(Comparator.comparingDouble(Machine::getTotalCapacityLeft)); //smallest to largest
        }

        if(typeOfOrder.equals("decreasing"))
            Collections.reverse(ret);           //decreasing

        return ret;
    }

    public static boolean FitsToMachine(Machine m, Task t)
    {
        if(m.MemoryLeft >= t.memoryRequest && m.CPULeft >= t.CPUrequest)
        // if(m.totalCapacityLeft>=(t.CPUrequest*t.memoryRequest))
        {
            return true;
        }
        return false;
    }
}




