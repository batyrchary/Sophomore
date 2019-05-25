import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.*;

public class ResourceAllocationGA
{

    public static class Pair
    {
        public int prob;
        public String server;

        public Pair(int p, String s)
        {
            this.prob=p;
            this.server=s;
        }
    }

    public static ArrayList<Integer> probs=new ArrayList<>();
    public static ArrayList<String> servers=new ArrayList<>();
    public static HashMap<String,Integer> latencies=new HashMap<>();

    public static ArrayList<Pair> pairs=new ArrayList<>();
    public static HashMap<Integer,ArrayList<String> > serversSeenByProb=new HashMap<>();

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    public static Random rand = new Random();
    public static ArrayList<Machine> MachineEvents=new ArrayList<>();
    public static ArrayList<Task> TaskEvents=new ArrayList<>();

    public static ArrayList<Task> decreasingTasksSortedByCPU=new ArrayList<>();
    public static ArrayList<Task> decreasingTasksSortedByMemory=new ArrayList<>();
    public static ArrayList<Task> decreasingTasksSortedBySpace=new ArrayList<>();
    public static ArrayList<Task> increasingTasksSortedByCPU=new ArrayList<>();
    public static ArrayList<Task> increasingTasksSortedByMemory=new ArrayList<>();
    public static ArrayList<Task> increasingTasksSortedBySpace=new ArrayList<>();

    public static ArrayList<Task> largestsmallestTasksbySpace=new ArrayList<>();

    public static ArrayList<Machine> decreasingMachinesSortedBySpace=new ArrayList<>();       //needs to be updated each time
    public static ArrayList<Machine> decreasingMachinesSortedByCPULeft=new ArrayList<>();     //needs to be updated each time
    public static ArrayList<Machine> decreasingMachinesSortedByMemoryLeft=new ArrayList<>();  //needs to be updated each time


    public static String XORtype="TwoPoint";
    public static String mutationType="Inversion";
    public static String selectionType="RouletteWheel";
    public static String fitnessType="hybrid";

    public static float crossoverProbability=0.9f;
    public static float mutationProbability=0.05f;


    ///////////////////////////////////////////////////////////////////

    public static int numberOfBitsInGene=5;
    public static int number_of_allocations=0;
    public static int maximumNumberOfMachines;

    ///////////////////////////////////////////////////////////////////

    public static String individualHeuristic="NAN";
    public static String individualParameter="NAN";


    public static boolean dynamic=true;
    public static HashMap<String,Integer> DynamicFromPrevious=new HashMap<>();
    public static HashMap<String,Integer> DynamicCurrent=new HashMap<>();
    public static float ratio=0;
    public static Stack<Chromosome> PreviousPopulation=null;

    public static class assignmentPair
    {
        public int tID;
        public int mID;
        public assignmentPair(int t, int m)
        {
            this.tID=t;
            this.mID=m;
        }
    }

    public static class PairU
    {
        public Machine m;
        public Task t;
        public int nextFitOffset=0;

        public PairU(Machine m, Task t, int n)
        {
            this.m=m;
            this.t=t;
            this.nextFitOffset=n;
        }
    }

    public static Population generateRandomPopulation(int numberOfIndividuals)
    {
        Population population=new Population();

        ArrayList<individualFitnessRunnable> threads=new ArrayList<>();

        for (float p=0; p<numberOfIndividuals; p++)
        {
            Chromosome c = new Chromosome();

            if((p/numberOfIndividuals) < ratio && PreviousPopulation!=null && dynamic==true && !PreviousPopulation.empty())
            {
               // Chromosome previousInd=PreviousPopulation.get((int) p);
                Chromosome previousInd=PreviousPopulation.pop();


                if(previousInd.size()<number_of_allocations)
                {
                    for (int i = 0; i < previousInd.size(); i++)
                    {
                        Gene g=new Gene(previousInd.chromosome.get(i));
                        c.add(g);
                    }
                    for (int i = previousInd.size(); i < number_of_allocations; i++)
                    {
                        Gene g = new Gene();
                        for (int j = 0; j < numberOfBitsInGene; j++) {
                            int random = (int) (Math.random() * 10 + 1);
                            g.add(random % 2);
                        }
                        c.add(g);
                    }
                }
                else
                {
                    for (int i = 0; i < number_of_allocations; i++)
                    {
                        Gene g=new Gene(previousInd.chromosome.get(i));
                        c.add(g);
                    }
                }
            }
            else
            {
                for (int i = 0; i < number_of_allocations; i++) {
                    Gene g = new Gene();
                    for (int j = 0; j < numberOfBitsInGene; j++) {
                        int random = (int) (Math.random() * 10 + 1);
                        g.add(random % 2);
                    }
                    c.add(g);
                }
            }
            c.hfitnes=individualFitness(c);
            population.add(c);
        }
        return population;
    }

    public static PairU TaskAllocator(int HeuristicCode, int parameter, ArrayList<Task> AllocatedTasks, PairU p)
    {
        Task taskToBeAssigned=p.t;

        // Task taskToBeAssigned=null;
        if(parameter==0 || parameter==11) //decreasingTasksSortedBySpace
        {
            for(int t=0; t<decreasingTasksSortedBySpace.size(); t++)
            {
                if(!Task.ContainsTask(AllocatedTasks,decreasingTasksSortedBySpace.get(t)))
                {
                    taskToBeAssigned=decreasingTasksSortedBySpace.get(t);
                    break;
                }
            }
        }
        else if(parameter==1)//increasingTasksSortedBySpace
        {
            for(int t=0; t<increasingTasksSortedBySpace.size(); t++)
            {
                if(!Task.ContainsTask(AllocatedTasks,increasingTasksSortedBySpace.get(t)))
                {
                    taskToBeAssigned=increasingTasksSortedBySpace.get(t);
                    break;
                }
            }
        }
        else if(parameter==10) //notsorted
        {
            for(int t=0; t<TaskEvents.size(); t++)
            {
                if(!Task.ContainsTask(AllocatedTasks,TaskEvents.get(t)))
                {
                    taskToBeAssigned=TaskEvents.get(t);
                    break;
                }
            }
        }
        else if(parameter==11) //largest-smallest
        {
            for(int t=0; t<largestsmallestTasksbySpace.size(); t++)
            {
                if(!Task.ContainsTask(AllocatedTasks,largestsmallestTasksbySpace.get(t)))
                {
                    taskToBeAssigned=largestsmallestTasksbySpace.get(t);
                    break;
                }
            }
        }
        return (new PairU(p.m,taskToBeAssigned,p.nextFitOffset));
        //  return taskToBeAssigned;
    }

    public static PairU MachineFinder(int HeuristicCode, ArrayList<Machine> openMachines,ArrayList<Machine> notOpenMachines, ArrayList<Task> AllocatedTasks, PairU p)
    {

        boolean NotFoundInOpen=true;

        Task taskToBeAssigned=p.t;
        Machine machineToAllocate=p.m;
        int nextFitOffset=p.nextFitOffset;

        if(HeuristicCode==0)                //FirstFit
        {
            for(int m=0; m<openMachines.size(); m++)
            {
                if(Machine.FitsToMachine(openMachines.get(m),taskToBeAssigned))
                {
                    machineToAllocate=openMachines.get(m);
                    NotFoundInOpen=false;
                    break;
                }
            }
        }
        else if(HeuristicCode==1 || HeuristicCode==11 || HeuristicCode==111 )           //BestFit & WorstFit & AlmostWorstFit
        {
            ArrayList<Machine> openMachinesSortedBySpace=Machine.MachineSorter(openMachines,"All", "decreasing");
            if(HeuristicCode==1)
            {
                for (int m = 0; m < openMachinesSortedBySpace.size(); m++) {

                    if(Machine.FitsToMachine(openMachinesSortedBySpace.get(m),taskToBeAssigned))
                    {
                        machineToAllocate = openMachinesSortedBySpace.get(m);
                        NotFoundInOpen = false;
                        break;
                    }
                }
            }
            if(HeuristicCode==11 || HeuristicCode==111)
            {
                int counter=0;
                for (int m = openMachinesSortedBySpace.size()-1; m >= 0; m--)
                {

                    if(Machine.FitsToMachine(openMachinesSortedBySpace.get(m), taskToBeAssigned))
                    {
                        counter++;
                        machineToAllocate = openMachinesSortedBySpace.get(m);
                        NotFoundInOpen = false;
                        if(HeuristicCode==11)
                            break;
                        else if(HeuristicCode==111 && counter==2)
                            break;
                    }
                }
            }
        }
        else if(HeuristicCode==10)          //NextFit
        {
            for(;nextFitOffset<openMachines.size();nextFitOffset++)
            {
                if(Machine.FitsToMachine(openMachines.get(nextFitOffset),taskToBeAssigned))
                {
                    machineToAllocate=openMachines.get(nextFitOffset);
                    NotFoundInOpen=false;
                    break;
                }
            }
        }
        else if(HeuristicCode==100)          //Filler
        {
            for(int i=0; i<openMachines.size(); i++)
            {
                for(int t=0; t<decreasingTasksSortedBySpace.size(); t++)
                {
                    Task task=decreasingTasksSortedBySpace.get(t);
                    if(!Task.ContainsTask(AllocatedTasks,task))
                    {
                        if(Machine.FitsToMachine(openMachines.get(i),task))
                        {
                            machineToAllocate=openMachines.get(i);
                            NotFoundInOpen=false;
                            taskToBeAssigned=task;
                            break;
                        }
                    }
                }
            }
        }
        else if(HeuristicCode==101 )          //Djang and Fitch (DJD).
        {
            ArrayList<Machine> openMachinesSortedBySpace=Machine.MachineSorter(openMachines,"All", "increasing");

            float waste=1000000000;

            for(int i=0; i<openMachinesSortedBySpace.size(); i++)
            {
                for(int t=0; t<decreasingTasksSortedBySpace.size(); t++)
                {
                    Task tt=decreasingTasksSortedBySpace.get(t);
                    Machine mm=openMachinesSortedBySpace.get(i);

                    if(!Task.ContainsTask(AllocatedTasks,tt))
                    {
                        if(Machine.FitsToMachine(mm,tt))
                        {
                            float wasteN=mm.totalCapacityLeft-(tt.memoryRequest*tt.CPUrequest);
                            if(waste>wasteN)
                            {
                                machineToAllocate=mm;
                                taskToBeAssigned=tt;
                                NotFoundInOpen=false;
                                waste=wasteN;
                            }
                        }
                    }
                }
            }
        }
        else if(HeuristicCode==110)                //Lastfit
        {
            for(int m=openMachines.size()-1; m>=0; m--)
            {
                if(Machine.FitsToMachine(openMachines.get(m),taskToBeAssigned))
                {
                    machineToAllocate=openMachines.get(m);
                    NotFoundInOpen=false;
                    break;
                }
            }
        }

        if(NotFoundInOpen)
        {
            for (int m = 0; m < notOpenMachines.size(); m++)
            {
                if(Machine.FitsToMachine(notOpenMachines.get(m), taskToBeAssigned))
                {
                    machineToAllocate = notOpenMachines.get(m);
                    break;
                }
            }
        }

        if(machineToAllocate==null)
        {
            for(int i=0; i<notOpenMachines.size(); i++)
            {
                if(notOpenMachines.get(i).CPULeft>taskToBeAssigned.CPUrequest && notOpenMachines.get(i).MemoryLeft>taskToBeAssigned.memoryRequest)
                    System.out.println(notOpenMachines.get(i).myMachineID);
            }
            System.out.println(taskToBeAssigned.memoryRequest+"\t"+taskToBeAssigned.CPUrequest);
            System.out.println("Cant Find Machine");
        }
        return (new PairU(machineToAllocate,taskToBeAssigned,nextFitOffset));
    }

    public static ArrayList<Integer> applyOneHeuristic(int H, int p)
    {
        int HeuristicCode=H;
        int parameter=p;

        //FFI
        //HeuristicCode=0;
        //parameter=1;
        if(individualHeuristic.equals("FFI"))
            HeuristicCode=0;
        if(individualParameter.equals("FFI"))
            parameter=1;


        //FFD
        //HeuristicCode=0;
        //parameter=0;
        if(individualHeuristic.equals("FFD"))
            HeuristicCode=0;
        if(individualParameter.equals("FFD"))
            parameter=0;

        //FF
        // HeuristicCode=0;
        // parameter=11;
        if(individualHeuristic.equals("FF"))
            HeuristicCode=0;
        if(individualParameter.equals("FF"))
            parameter=11;



        //BFI
        //HeuristicCode=1;
        //parameter=1;
        if(individualHeuristic.equals("BFI"))
            HeuristicCode=1;
        if(individualParameter.equals("BFI"))
            parameter=1;



        //BFD
//             HeuristicCode=1;
        //            parameter=0;
        if(individualHeuristic.equals("BFD"))
            HeuristicCode=1;
        if(individualParameter.equals("BFD"))
            parameter=0;



        //BF
        //  HeuristicCode=1;
        //  parameter=11;
        if(individualHeuristic.equals("BF"))
            HeuristicCode=1;
        if(individualParameter.equals("BF"))
            parameter=11;

        //WFI
        //  HeuristicCode=11;
        //  parameter=1;
        if(individualHeuristic.equals("WFI"))
            HeuristicCode=11;
        if(individualParameter.equals("WFI"))
            parameter=1;


        //WFD
        //HeuristicCode=11;
        //parameter=0;
        if(individualHeuristic.equals("WFD"))
            HeuristicCode=11;
        if(individualParameter.equals("WFD"))
            parameter=0;


        //WF
        //  HeuristicCode=11;
        //  parameter=11;
        if(individualHeuristic.equals("WF"))
            HeuristicCode=11;
        if(individualParameter.equals("WF"))
            parameter=11;


        //AWFI
        //HeuristicCode=111;
        //parameter=1;

        if(individualHeuristic.equals("AWFI"))
            HeuristicCode=111;
        if(individualParameter.equals("AWFI"))
            parameter=1;


        //AWFD
        // HeuristicCode=111;
        // parameter=0;
        if(individualHeuristic.equals("AWFD"))
            HeuristicCode=111;
        if(individualParameter.equals("AWFD"))
            parameter=0;


        //AWF
        //HeuristicCode=111;
        //parameter=11;

        if(individualHeuristic.equals("AWF"))
            HeuristicCode=111;
        if(individualParameter.equals("AWF"))
            parameter=11;


        //NFI
        // HeuristicCode=10;
        // parameter=1;
        if(individualHeuristic.equals("NFI"))
            HeuristicCode=10;
        if(individualParameter.equals("NFI"))
            parameter=1;


        //NFD
        // HeuristicCode=10;
        // parameter=0;

        if(individualHeuristic.equals("NFD"))
            HeuristicCode=10;
        if(individualParameter.equals("NFD"))
            parameter=0;

        //NF
        // HeuristicCode=10;
        // parameter=11;

        if(individualHeuristic.equals("NF"))
            HeuristicCode=10;
        if(individualParameter.equals("NF"))
            parameter=11;

        //Filler
        //HeuristicCode=100;
        if(individualHeuristic.equals("Filler"))
            HeuristicCode=100;


        //Djang and Fitch
        //HeuristicCode=101;
        if(individualHeuristic.equals("DJF"))
            HeuristicCode=101;


        ArrayList<Integer> ret=new ArrayList<>();
        ret.add(HeuristicCode);
        ret.add(parameter);

        return ret;
    }


    public static class individualFitnessRunnable implements Runnable {
        Chromosome individual;
        String name;
        Thread t;
        public individualFitnessRunnable(Chromosome individual, String nameOfThread)
        {
            this.individual = individual;
            this.name=nameOfThread;

            t=new Thread(this, name);
            t.start();
        }
        @Override
        public void run() {
            individual.hfitnes=individualFitness(individual);
        }
    }

    public static Chromosome.Fitness individualFitness(Chromosome individual)
    {
        ArrayList<Task> AllocatedTasks=new ArrayList<>();
        ArrayList<Machine> openMachines=new ArrayList<>();
        ArrayList<Machine> notOpenMachines=Machine.CopyMachines(MachineEvents);

        ArrayList<String> assignmentPairs=new ArrayList<>();


        individual.assignments.clear();

        PairU p=new PairU(null,null, 0);

        for(int i=0; i<number_of_allocations; i=i+1)
        {
            p.m=null;
            p.t=null;

            //get heuristic and parameter code//
            //------------------------------------------------------------------------------//
            Gene gene=individual.get(i);
            //000->0   001->1   010->10  011->11    100->100, 101->101, 110->110,    111->111
            int HeuristicCode=gene.get(0)*100+gene.get(1)*10+gene.get(2);
            int parameter=gene.get(3)*10+gene.get(4);

           /*
            ArrayList<Integer> ret=applyOneHeuristic(HeuristicCode,parameter);
             HeuristicCode=ret.get(0);
             parameter=ret.get(1);
          */

            //------------------------------------------------------------------------------//

            //find machine and task to allocate//
            //------------------------------------------------------------------------------//
            p=TaskAllocator(HeuristicCode,parameter,AllocatedTasks,p);
            p=MachineFinder(HeuristicCode,openMachines,notOpenMachines, AllocatedTasks,p);
            //------------------------------------------------------------------------------//

            Task taskToBeAssigned=p.t;
            Machine machineToAllocate=p.m;

            //make update//
            //------------------------------------------------------------------------------//
            AllocatedTasks.add(taskToBeAssigned);

            machineToAllocate=Machine.UpdateMachine(machineToAllocate,taskToBeAssigned);

            int indexInOpen=Machine.ContainsMachine(openMachines,machineToAllocate);
            int indexInNotOpen=Machine.ContainsMachine(notOpenMachines,machineToAllocate);
            if(indexInOpen==-1)
            {
                openMachines.add(machineToAllocate);
            }
            else
            {
                openMachines.set(indexInOpen,machineToAllocate);
            }
            if(indexInNotOpen!=-1)
            {
                notOpenMachines.remove(indexInNotOpen);
            }
            //------------------------------------------------------------------------------//

            individual.assignments.add(new assignmentPair(taskToBeAssigned.taskID,machineToAllocate.myMachineID));

            int probID=taskToBeAssigned.probid;
            String serverId=machineToAllocate.server;

            String ppp="prb="+String.valueOf(probID)+",server="+serverId;
            assignmentPairs.add(ppp);
        }
        //    System.out.println();


        float overallLatency=0;
        for(int i=0; i<assignmentPairs.size(); i++)
        {
            if(latencies.containsKey(assignmentPairs.get(i)))
            {
                overallLatency=overallLatency+latencies.get(assignmentPairs.get(i));
            }
            else
            {
                overallLatency=overallLatency+500;
            }
        }

        overallLatency=overallLatency/assignmentPairs.size();

        individual.bins=openMachines.size();
        individual.latency=overallLatency;

        float bscore=1.0f/openMachines.size();;

        float lscore=1.0f/overallLatency;

        float hscore=bscore+lscore;

        return new Chromosome.Fitness(bscore,lscore,hscore);
    }

    public static float averageFitness(Population population)
    {
        float fitness=0;
        for(int i=0; i<population.size();i++)
        {
            fitness=fitness+population.get(i).getFitness(fitnessType);
        }
        return fitness/population.size();
    }

    public static Population GenerateNewGeneration(Population generation)
    {
        Population newGeneration=new Population();

        ArrayList<individualFitnessRunnable> threads=new ArrayList<>();

        for(int i=0; i<generation.size()/2; i++)
        {
            //System.out.println("i="+i);
           // Chromosome parent1=new Chromosome(IndividualSelection.RouletteWheel(generation, maximumNumberOfMachines,fitnessType));
           // Chromosome parent2=new Chromosome(IndividualSelection.RouletteWheel(generation,maximumNumberOfMachines,fitnessType));

            Chromosome parent1=new Chromosome(IndividualSelection.Tournament(generation, "bin"));
            Chromosome parent2=new Chromosome(IndividualSelection.Tournament(generation,"latency"));

            Chromosome kid1=new Chromosome(parent1);
            Chromosome kid2=new Chromosome(parent2);
            if(rand.nextFloat()<crossoverProbability)
            {
                ArrayList<Chromosome> kids = CrossOver.Crossover(parent1,parent2,XORtype);
                kid1 = kids.get(0);
                kid2 = kids.get(1);
            }
            if(rand.nextFloat()<mutationProbability)
            {
                kid1=Mutation.Mutation(kid1,mutationType);
            }
            if(rand.nextFloat()<mutationProbability)
            {
                kid2=Mutation.Mutation(kid2,mutationType);
            }


            individualFitnessRunnable fit1 = new individualFitnessRunnable(kid1, "kid1");
            //new Thread(fit1).start();

            individualFitnessRunnable fit2 = new individualFitnessRunnable(kid2, "kid2");
            //new Thread(fit2).start();

            threads.add(fit1);
            threads.add(fit2);


    /*
            kid1.fitness=individualFitness(kid1);
            kid2.fitness=individualFitness(kid2);

            newGeneration.add(kid1);
            newGeneration.add(kid2);
  */
        }
        for(int i=0; i<threads.size(); i++)
        {
            try {
                threads.get(i).t.join();
                newGeneration.add(threads.get(i).individual);
            }catch (Exception e) { }
        }
        return newGeneration;
    }

    public static Population Selection(Population prevGeneration, Population newGeneration)
    {
        Population ret=prevGeneration.addTwoPopulation(prevGeneration,newGeneration);

        Population retf=Pareto.ParetoSelection(ret);

        /*
        ret=ret.sortByFitness(ret,fitnessType);

        Population retf=new Population();

        for(int i=0; i<prevGeneration.size(); i++)
        {
            retf.add(ret.get(i));
        }
        */
        return retf;

    }


    public static void printer(Population p, int counter, int problemInstance, int testcase, FileWriter fileWriter)
    {
        try {
            FileWriter assWriter = new FileWriter("/home/cc/output/128/" +testcase+"/128-"+problemInstance+"/p128-"+counter+".csv");

            float bins=0;
            float latency=0;
            for (int i = 0; i < p.size(); i++) {

                bins=bins+p.get(i).bins;
                latency=latency+p.get(i).latency;

                //System.out.println(counter+"\tbins="+p.get(i).bins+"\tlatency="+p.get(i).latency);
                //System.out.println(counter + "," + p.get(i).getFitness("bin") + "," + p.get(i).getFitness("latency")+"\n");
                assWriter.write(counter + "," + p.get(i).getFitness("bin") + "," + p.get(i).getFitness("latency")+"\n");
            }

            fileWriter.write(bins/100+","+latency/100+"\n");
            //System.out.println(counter+"\tbins="+bins/100+"\tlatency="+latency/100);

            assWriter.close();
        }catch (Exception e){e.printStackTrace();}
    }

    public static ArrayList<assignmentPair> GA(int population, int consecutiveGenerations, float minDifferenceInFitness,  int maximumG, FileWriter fileWriter, int problemInstance, int testcase)
    {
        try
        {
            float prevAvgFit = 0;
            float newAvgFit = 0;
            int consGeneration = 0;

            Population initialPop = generateRandomPopulation(population);

            Population prevGeneration = initialPop;
            Population newGeneration = initialPop;

            prevAvgFit = averageFitness(prevGeneration);
            newAvgFit = averageFitness(newGeneration);

            long startTime = System.currentTimeMillis();

            int counter = 0;
            while (counter < maximumG)
            {
                prevAvgFit = newAvgFit;

                newGeneration = GenerateNewGeneration(prevGeneration);

                newAvgFit = averageFitness(newGeneration);

                prevGeneration = Selection(prevGeneration, newGeneration);

                if(Math.abs(prevAvgFit-newAvgFit)<minDifferenceInFitness)
                    consGeneration++;
                else
                    consGeneration=0;

                counter++;

                printer(prevGeneration,counter,problemInstance, testcase,fileWriter);


                for(int pp=0; pp<prevGeneration.size(); pp=(pp+1)*4)
                {
                    PreviousPopulation.push(prevGeneration.get(pp));
                }

            }

           // PreviousPopulation=prevGeneration;

            Chromosome best= prevGeneration.get(0);

            return best.assignments;
        }catch (Exception e){e.printStackTrace();}
        return null;
    }

    public static void main(String[] args) throws Exception
    {
        System.out.println("hello");

/*

        String p1 = "/home/cc/input/edgeU.csv";
        String p2 = "/home/cc/input/MachineC.csv";

        String p3="/home/cc/input/128.csv";


        FileWriter pWriter = new FileWriter("/home/cc/output/128sout.csv");



//        dynamic=false;

        for(int j=1; j<=30; j++)//30
        {
        //    j=31;
            DynamicFromPrevious=new HashMap<>();
            DynamicCurrent=new HashMap<>();
            ratio=0;
            PreviousPopulation=new Stack<>();

            for (int i = 1; i <= 500; i++)//5
            {
       // int i=1;
                //number_of_allocations = 512;
                maximumNumberOfMachines = 300;

                ReadDataU(p1, p2, p3, i);



                ////////////////////////////////////////////////////
                crossoverProbability = 0.95f;
                mutationProbability = 0.05f;

                mutationType = "Inversion";   //SingleBitFlip, Inversion, Flip
                XORtype = "TwoPoint";         //SinglePoint,   TwoPoint
                fitnessType = "hybrid";
                ////////////////////////////////////////////////////

              //  decreasingTasksSortedByCPU = Task.TaskSorter(TaskEvents, "CPU", "decreasing");
             //   decreasingTasksSortedByMemory = Task.TaskSorter(TaskEvents, "Memory", "decreasing");
             //   increasingTasksSortedByCPU = Task.TaskSorter(TaskEvents, "CPU", "increasing");
             //   increasingTasksSortedByMemory = Task.TaskSorter(TaskEvents, "Memory", "increasing");
                increasingTasksSortedBySpace = Task.TaskSorter(TaskEvents, "All", "increasing");
                decreasingTasksSortedBySpace = Task.TaskSorter(TaskEvents, "All", "decreasing");

//                largestsmallestTasksbySpace = Task.newTaskSorter(decreasingTasksSortedBySpace, "largesmall", "decreasing");

                decreasingMachinesSortedBySpace = Machine.MachineSorter(MachineEvents, "All", "decreasing");
                decreasingMachinesSortedByCPULeft = Machine.MachineSorter(MachineEvents, "CPU", "decreasing");
                decreasingMachinesSortedByMemoryLeft = Machine.MachineSorter(MachineEvents, "Memory", "decreasing");

                //////
                numberOfBitsInGene = 5;

                number_of_allocations = TaskEvents.size();
                //maximumNumberOfMachines = MachineEvents.size();

                ////////

            //    System.out.println("dynamicCurrent=" + DynamicCurrent.size());
            //    System.out.println("dynamicPrevious=" + DynamicFromPrevious.size());


                long startTime = System.currentTimeMillis();

                pWriter.write(i+","+j+","+ratio+","+TaskEvents.size()+"\n");

                ArrayList<assignmentPair> assignments = GA(100, 10, 0.5f, 30, pWriter, i, j);




                System.out.println("ratio=" + ratio);
                System.out.println("Tasks="+TaskEvents.size());
                System.out.println("i="+i+"\tj="+j);



                MachineEvents.clear();
                TaskEvents.clear();

               // decreasingTasksSortedByCPU.clear();
              //  decreasingTasksSortedByMemory.clear();
              //  increasingTasksSortedByCPU.clear();
             //   increasingTasksSortedByMemory.clear();
                increasingTasksSortedBySpace.clear();
                decreasingTasksSortedBySpace.clear();

                decreasingMachinesSortedBySpace.clear();
                decreasingMachinesSortedByCPULeft.clear();
                decreasingMachinesSortedByMemoryLeft.clear();

                probs.clear();
                servers.clear();
                latencies.clear();
                pairs.clear();
                serversSeenByProb.clear();
            }
        }
        pWriter.close();


    */

    }



    public static void ReadDataU(String ServerUserLatencyMapping, String machineEvents, String taskEvents,int coming)
    {
        try
        {
            File file = new File(ServerUserLatencyMapping);

            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;
            while ((line = br.readLine()) != null) {
                String splitted[] = line.replace(",,", ",").split(",");
                if (splitted[0].equals("prb"))
                    continue;

                int prb = Integer.parseInt(splitted[0]);
                ArrayList<String> serversForPrb=new ArrayList<>();
                for (int i = 1; i < splitted.length; i = i + 2) {
                    float latency = Float.parseFloat(splitted[i]);
                    String server = splitted[i + 1];

                    serversForPrb.add(server);
                    ResourceAllocationGA.Pair pair = new ResourceAllocationGA.Pair(prb, server);
                    pairs.add(pair);

                    int intlatency=Math.round(latency);

                    String p="prb="+String.valueOf(prb)+",server="+server;
                    latencies.put(p,intlatency);
                    //latencies.put(pair, intlatency);

                    if (!servers.contains(server))
                        servers.add(server);
                }
                serversSeenByProb.put(prb,serversForPrb);
                probs.add(prb);
            }
            br.close();
        }catch (Exception e){ System.out.println("exception in reading2"); }


        ////
        try
        {
            int taskID=0;
            File file = new File(taskEvents);

            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;

            float numerator=0;

            while ((line = br.readLine()) != null)
            {
                String splitted[]=line.split(",");

                if (line.contains("coming"))
                {
                    continue;
                }

                int com=Integer.parseInt(splitted[0]);

                if (com>coming)
                {
                    break;
                }
                if(com<coming)
                {
                    continue;
                }

                String jobid=splitted[1];

                float CPUrequest = Float.parseFloat(splitted[4]);           //new
                float memoryRequest = Float.parseFloat(splitted[5]);        //new
                int leaving=Integer.parseInt(splitted[6]);


                if(CPUrequest<1)
                {
                    CPUrequest=CPUrequest;
                }
               // else if(CPUrequest*10>=1){
               //     System.out.println("a");
               // }
                if(memoryRequest<1)
                {
                    memoryRequest=memoryRequest;
                }
                //else if(memoryRequest*10>=1){
                //    System.out.println("b");
                //}



                int probId=probs.get(taskID%probs.size());

                if(DynamicFromPrevious.containsKey(jobid))
                {
                    probId=DynamicFromPrevious.get(jobid);
                    numerator++;

                }

                ratio=(numerator)/DynamicCurrent.size();

                DynamicCurrent.put(jobid,probId);

                TaskEvents.add(new Task(taskID,CPUrequest,memoryRequest,probId));

                //if(taskID+1==number_of_allocations)
                //    break;

                taskID++;
            }



            DynamicFromPrevious.clear();

            DynamicCurrent.forEach((key,value) -> DynamicFromPrevious.put(key,value));

            DynamicCurrent.clear();

            br.close();

        }catch (Exception e){
            e.printStackTrace();
            System.out.println("exception in reading taskevents");
        }

        try
        {
            File file = new File(machineEvents);

            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;

            int MyMachineId=0;

            while ((line = br.readLine()) != null)
            {
                String splitted []=line.split(",");

                float CPU;
                float Memory;

                CPU=Float.parseFloat(splitted[1]);
                Memory=Float.parseFloat(splitted[2]);
                //MyMachineId=Integer.parseInt(splitted[0]);

                String server=servers.get(MyMachineId%servers.size());

                MachineEvents.add(new Machine(MyMachineId,CPU,Memory,server));

                if(MyMachineId+1==maximumNumberOfMachines)
                    break;

                MyMachineId++;
            }
            br.close();
        }catch (Exception e){ System.out.println("exception in reading"); }
    }


}
