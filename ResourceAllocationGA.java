import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.*;

public class ResourceAllocationGA
{

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    public static Random rand = new Random();
    public static ArrayList<Bin> Bins=new ArrayList<>();
    public static ArrayList<Item> Items=new ArrayList<>();

    public static ArrayList<Item> decreasingItemsSortedByWidth =new ArrayList<>();
    public static ArrayList<Item> decreasingItemsSortedByHeight=new ArrayList<>();
    public static ArrayList<Item> increasingItemsSortedByWidth =new ArrayList<>();
    public static ArrayList<Item> increasingItemsSortedByHeight =new ArrayList<>();
    public static ArrayList<Item> increasingItemsSortedBySpace =new ArrayList<>();
    public static ArrayList<Item> decreasingItemsSortedBySpace =new ArrayList<>();

    public static ArrayList<Bin> decreasingBinsSortedBySpace =new ArrayList<>();       //needs to be updated each time
    public static ArrayList<Bin> decreasingBinsSortedByCPULeft =new ArrayList<>();       //needs to be updated each time
    public static ArrayList<Bin> decreasingBinsSortedByMemoryLeft =new ArrayList<>();       //needs to be updated each time

    public static String XORtype="TwoPoint";
    public static String mutationType="Inversion";
    public static String selectionType="RouletteWheel";


    public static float crossoverProbability=0.9f;
    public static float mutationProbability=0.05f;

    public static int population=100;
    public static int consecutive_generations=10;
    public static double minFitnessDifference=0.5;
    public static int  maximumGenerations=50;

    public static int numberOfBitsInGene=5;
    public static int number_of_allocations=0;


    ///////////////////////////////////////////////////////////////////

    public static String individualHeuristic="NAN";
    public static String individualParameter="NAN";


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
        public Bin m;
        public Item t;
        public int nextFitOffset=0;

        public PairU(Bin m, Item t, int n)
        {
            this.m=m;
            this.t=t;
            this.nextFitOffset=n;
        }
    }

    public static Population generateRandomPopulation(int numberOfIndividuals)
    {
        Population population=new Population();

        for (float p=0; p<numberOfIndividuals; p++)
        {
            Chromosome c = new Chromosome();

            for (int i = 0; i < number_of_allocations; i++) {
                Gene g = new Gene();
                for (int j = 0; j < numberOfBitsInGene; j++) {
                    int random = (int) (Math.random() * 10 + 1);
                    g.add(random % 2);
                }
                c.add(g);
            }
            //c.fitness=individualFitness(c);
            c.bins=individualFitness(c);
            c.fitness=1.0f/c.bins;

            population.add(c);
        }
        return population;
    }


    public static float averageFitness(Population population)
    {
        float fitness=0;
        for(int i=0; i<population.size();i++)
        {
            fitness=fitness+population.get(i).fitness;
        }
        return fitness/population.size();
    }


    public static PairU itemAllocator(int HeuristicCode, int parameter, ArrayList<Item> AllocatedItem, PairU p)
    {
        Item itemToBeAssigned=p.t;

        // item itemToBeAssigned=null;
        if(parameter==0 || parameter==11) //decreasingitemsSortedBySpace
        {
            for(int t=0; t<decreasingItemsSortedBySpace.size(); t++)
            {
                if(!Item.ContainsItem(AllocatedItem,decreasingItemsSortedBySpace.get(t)))
                {
                    itemToBeAssigned=decreasingItemsSortedBySpace.get(t);
                    break;
                }
            }
        }
        else if(parameter==1)//increasingitemsSortedBySpace
        {
            for(int t=0; t<increasingItemsSortedBySpace.size(); t++)
            {
                if(!Item.ContainsItem(AllocatedItem,increasingItemsSortedBySpace.get(t)))
                {
                    itemToBeAssigned=increasingItemsSortedBySpace.get(t);
                    break;
                }
            }
        }
        else if(parameter==10) //notsorted
        {
            for(int t=0; t<Items.size(); t++)
            {
                if(!Item.ContainsItem(AllocatedItem,Items.get(t)))
                {
                    itemToBeAssigned=Items.get(t);
                    break;
                }
            }
        }

        return (new PairU(p.m,itemToBeAssigned,p.nextFitOffset));
        //  return itemToBeAssigned;
    }

    public static PairU BinFinder(int HeuristicCode, ArrayList<Bin> openBins,ArrayList<Bin> notopenBins, ArrayList<Item> AllocatedItem, PairU p)
    {


        boolean NotFoundInOpen=true;

        Item itemToBeAssigned=p.t;
        Bin BinToAllocate=p.m;
        int nextFitOffset=p.nextFitOffset;

        if(HeuristicCode==0)                //FirstFit
        {
            for(int m=0; m<openBins.size(); m++)
            {
                if(Bin.FitsToBin(openBins.get(m),itemToBeAssigned))
                {
                    BinToAllocate=openBins.get(m);
                    NotFoundInOpen=false;
                    break;
                }
            }
        }
        else if(HeuristicCode==1 || HeuristicCode==11 || HeuristicCode==111 )           //BestFit & WorstFit & AlmostWorstFit
        {
            ArrayList<Bin> openBinsSortedBySpace=Bin.BinSorter(openBins,"All", "decreasing");
            if(HeuristicCode==1)
            {
                for (int m = 0; m < openBinsSortedBySpace.size(); m++) {

                    if(Bin.FitsToBin(openBinsSortedBySpace.get(m),itemToBeAssigned))
                    {
                        BinToAllocate = openBinsSortedBySpace.get(m);
                        NotFoundInOpen = false;
                        break;
                    }
                }
            }
            if(HeuristicCode==11 || HeuristicCode==111)
            {
                int counter=0;
                for (int m = openBinsSortedBySpace.size()-1; m >= 0; m--)
                {

                    if(Bin.FitsToBin(openBinsSortedBySpace.get(m), itemToBeAssigned))
                    {
                        counter++;
                        BinToAllocate = openBinsSortedBySpace.get(m);
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
            for(;nextFitOffset<openBins.size();nextFitOffset++)
            {
                if(Bin.FitsToBin(openBins.get(nextFitOffset),itemToBeAssigned))
                {
                    BinToAllocate=openBins.get(nextFitOffset);
                    NotFoundInOpen=false;
                    break;
                }
            }
        }
        else if(HeuristicCode==100)          //Filler
        {
            for(int i=0; i<openBins.size(); i++)
            {
                for(int t=0; t<decreasingItemsSortedBySpace.size(); t++)
                {
                    Item item=decreasingItemsSortedBySpace.get(t);
                    if(!Item.ContainsItem(AllocatedItem,item))
                    {
                        if(Bin.FitsToBin(openBins.get(i),item))
                        {
                            BinToAllocate=openBins.get(i);
                            NotFoundInOpen=false;
                            itemToBeAssigned=item;
                            break;
                        }
                    }
                }
            }
        }
        else if(HeuristicCode==101 )          //Djang and Fitch (DJD).
        {
            ArrayList<Bin> openBinsSortedBySpace=Bin.BinSorter(openBins,"All", "increasing");

            float waste=1000000000;

            for(int i=0; i<openBinsSortedBySpace.size(); i++)
            {
                for(int t=0; t<decreasingItemsSortedBySpace.size(); t++)
                {
                    Item tt=decreasingItemsSortedBySpace.get(t);
                    Bin mm=openBinsSortedBySpace.get(i);

                    if(!Item.ContainsItem(AllocatedItem,tt))
                    {
                        if(Bin.FitsToBin(mm,tt))
                        {
                            float wasteN=mm.totalCapacityLeft-(tt.heightRequest*tt.widthRequest);
                            if(waste>wasteN)
                            {
                                BinToAllocate=mm;
                                itemToBeAssigned=tt;
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
            for(int m=openBins.size()-1; m>=0; m--)
            {
                if(Bin.FitsToBin(openBins.get(m),itemToBeAssigned))
                {
                    BinToAllocate=openBins.get(m);
                    NotFoundInOpen=false;
                    break;
                }
            }
        }

        if(NotFoundInOpen)
        {
            for (int m = 0; m < notopenBins.size(); m++)
            {
                if(Bin.FitsToBin(notopenBins.get(m), itemToBeAssigned))
                {
                    BinToAllocate = notopenBins.get(m);
                    break;
                }
            }
        }

        if(BinToAllocate==null)
        {

            for(int i=0; i<notopenBins.size(); i++)
            {
                if(notopenBins.get(i).widthLeft>itemToBeAssigned.widthRequest && notopenBins.get(i).heightLeft>itemToBeAssigned.heightRequest)
                    System.out.println(notopenBins.get(i).binID);
            }
            System.out.println(itemToBeAssigned.heightRequest+"\t"+itemToBeAssigned.widthRequest);
            System.out.println("Cant Find Bin");
        }
        return (new PairU(BinToAllocate,itemToBeAssigned,nextFitOffset));
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
            //individual.fitness=individualFitness(individual);
            individual.bins=individualFitness(individual);
            individual.fitness=1.0f/individual.bins;
        }
    }

    public static int individualFitness(Chromosome individual)
    {
        ArrayList<Item> AllocatedItem=new ArrayList<>();
        ArrayList<Bin> openBins=new ArrayList<>();
        ArrayList<Bin> notopenBins=Bin.CopyBins(Bins);

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
            HeuristicCode=0;
            parameter=0;
            ArrayList<Integer> ret=applyOneHeuristic(HeuristicCode,parameter);
            HeuristicCode=ret.get(0);
            parameter=ret.get(1);
            */


            //------------------------------------------------------------------------------//

            //find Bin and item to allocate//
            //------------------------------------------------------------------------------//
            p=itemAllocator(HeuristicCode,parameter,AllocatedItem,p);
            p=BinFinder(HeuristicCode,openBins,notopenBins, AllocatedItem,p);
            //------------------------------------------------------------------------------//

            Item itemToBeAssigned=p.t;
            Bin BinToAllocate=p.m;

            //make update//
            //------------------------------------------------------------------------------//
            AllocatedItem.add(itemToBeAssigned);

            BinToAllocate=Bin.UpdateBin(BinToAllocate,itemToBeAssigned);

            int indexInOpen=Bin.ContainsBin(openBins,BinToAllocate);
            int indexInNotOpen=Bin.ContainsBin(notopenBins,BinToAllocate);
            if(indexInOpen==-1)
            {
                openBins.add(BinToAllocate);
            }
            else
            {
                openBins.set(indexInOpen,BinToAllocate);
            }
            if(indexInNotOpen!=-1)
            {
                notopenBins.remove(indexInNotOpen);
            }
            //------------------------------------------------------------------------------//

            individual.assignments.add(new assignmentPair(itemToBeAssigned.itemID,BinToAllocate.binID));

        }


        return openBins.size();
        //float bscore=1.0f/openBins.size();;
        // return bscore;
    }

    public static Population GenerateNewGeneration(Population generation)
    {
        Population newGeneration=new Population();

        ArrayList<individualFitnessRunnable> threads=new ArrayList<>();

        for(int i=0; i<generation.size()/2; i++)
        {
            Chromosome parent1=new Chromosome(IndividualSelection.RouletteWheel(generation));
            Chromosome parent2=new Chromosome(IndividualSelection.RouletteWheel(generation));

           // Chromosome parent1=new Chromosome(IndividualSelection.Tournament(generation));
           // Chromosome parent2=new Chromosome(IndividualSelection.Tournament(generation));

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
           // kid1.fitness=individualFitness(kid1);
           // kid2.fitness=individualFitness(kid2);

            kid1.bins=individualFitness(kid1);
            kid1.fitness=1.0f/kid1.bins;

            kid2.bins=individualFitness(kid2);
            kid2.fitness=1.0f/kid2.bins;

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

        ret=ret.sortByFitness(ret);

        //for (int i=0;i<ret.size();i++)
        //{
        //    System.out.println("fit="+ret.get(i).fitness);
        //}


        Population retf=new Population();

        for(int i=0; i<prevGeneration.size(); i++)
        {
            retf.add(ret.get(i));
        }
        return retf;
    }

    public static ArrayList<assignmentPair> GA(String output_file)
    {
        try
        {
            FileWriter writer = new FileWriter(output_file);

            float prevAvgFit = 0;
            float newAvgFit = 0;
            int consGeneration = 0;

            Population initialPop = generateRandomPopulation(population);

            Population prevGeneration = initialPop;
            Population newGeneration = initialPop;

            prevAvgFit = averageFitness(prevGeneration);
            newAvgFit = averageFitness(newGeneration);

            int counter = 0;

            System.out.println("Generation,averageFitness,BestFitness, leastOpenedBins");
            writer.write("Generation,averageFitness,BestFitness, leastOpenedBins\n");
            //while (counter < maximumGenerations && consGeneration <consecutive_generations)
            while (counter < maximumGenerations)
            {
                prevAvgFit = newAvgFit;

                newGeneration = GenerateNewGeneration(prevGeneration);

                newAvgFit = averageFitness(newGeneration);

                prevGeneration = Selection(prevGeneration, newGeneration);

                if(Math.abs(prevAvgFit-newAvgFit)<minFitnessDifference)
                    consGeneration++;
                else
                    consGeneration=0;

                counter++;

                System.out.println(counter+","+prevAvgFit+","+prevGeneration.get(0).fitness+","+prevGeneration.get(0).bins);
                writer.write(counter+","+prevAvgFit+","+prevGeneration.get(0).fitness+","+prevGeneration.get(0).bins+"\n");
            }
            writer.close();

            Chromosome best= prevGeneration.get(0);

            return best.assignments;

        }catch (Exception e){e.printStackTrace();}
        return null;
    }

    public static void main(String[] args) throws Exception
    {

        String output_file = "./output.csv";

        String path_bin = "./example_input/example_bin_input.csv";
        String path_item = "./example_input/example_item_input.csv";
        String path_toConfig="./example_input/config.txt";



        if (args.length > 4)
        {
            path_bin = args[0];
            path_item = args[1];
            path_toConfig = args[2];
            output_file = args[3];
        }


        ReadData(path_bin, path_item, path_toConfig);

        System.out.println("#items="+Items.size());
        System.out.println("#bins="+Bins.size());

        decreasingItemsSortedByWidth = Item.ItemSorter(Items, "Width", "decreasing");
        decreasingItemsSortedByHeight = Item.ItemSorter(Items, "Height", "decreasing");
        increasingItemsSortedByWidth = Item.ItemSorter(Items, "Width", "increasing");
        increasingItemsSortedByHeight = Item.ItemSorter(Items, "Height", "increasing");
        increasingItemsSortedBySpace = Item.ItemSorter(Items, "All", "increasing");
        decreasingItemsSortedBySpace = Item.ItemSorter(Items, "All", "decreasing");



        decreasingBinsSortedBySpace = Bin.BinSorter(Bins, "All", "decreasing");
        decreasingBinsSortedByCPULeft = Bin.BinSorter(Bins, "Width", "decreasing");
        decreasingBinsSortedByMemoryLeft = Bin.BinSorter(Bins, "Height", "decreasing");

        //////
        numberOfBitsInGene = 5;
        number_of_allocations = Items.size();

        ArrayList<assignmentPair> assignments = GA(output_file);
    }

    public static void ReaderHelper(String path, int type)
    {
        try
        {
            File file = new File(path);

            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;
            int id=0;
            while ((line = br.readLine()) != null)
            {
                String splitted[] = line.split(",");
                if (splitted[0].equals("width"))
                    continue;

                int width=Integer.parseInt(splitted[0]);
                int height=Integer.parseInt(splitted[1]);
                int number=Integer.parseInt(splitted[2]);

                for(int i=0; i<number; i++)
                {
                    if(type==1)
                    {
                        Bins.add(new Bin(id, width, height));
                    }
                    else
                    {
                        Items.add(new Item(id, width, height));
                    }
                    id++;
                }
            }
            br.close();
        }catch (Exception e){ System.out.println("exception in ReaderHelper"); }
    }

    public static void ReadData(String path_bin, String path_item, String path_toConfig)
    {

        try {
            File file = new File(path_toConfig);

            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;

            while ((line = br.readLine()) != null) {

                line=line.split(";")[0];

                String argument=line.split("=")[0];
                String paramter=line.split("=")[1];

                if(argument.equals("XORtype"))
                {
                    XORtype=paramter;
                }
                if(argument.equals("mutationType"))
                {
                    mutationType=paramter;
                }
                if(argument.equals("selectionType"))
                {
                    selectionType=paramter;
                }
                if(argument.equals("crossoverProbability"))
                {
                    crossoverProbability=Float.parseFloat(paramter);
                }
                if(argument.equals("mutationProbability"))
                {
                    mutationProbability=Float.parseFloat(paramter);
                }
                if(argument.equals("population"))
                {
                    population=Integer.parseInt(paramter);
                }
                if(argument.equals("mutationProbability"))
                {
                    mutationProbability=Float.parseFloat(paramter);
                }
                if(argument.equals("mutationProbability"))
                {
                    mutationProbability=Float.parseFloat(paramter);
                }
                if(argument.equals("minFitnessDifference"))
                {
                    minFitnessDifference=Float.parseFloat(paramter);
                }
                if(argument.equals("maximumGenerations"))
                {
                    maximumGenerations=Integer.parseInt(paramter);
                }

            }
        }catch (Exception e){ System.out.println("exception in configReader"); }


/*
        XORtype="TwoPoint";         //SinglePoint,   TwoPoint
        mutationType="Inversion";   //SingleBitFlip, Inversion, Flip
        selectionType="RouletteWheel";

        crossoverProbability=0.95f;
        mutationProbability=0.05f;
        population=100;
        consecutive_generations=10;
        minFitnessDifference=0.5;
        maximumGenerations=1;
*/

        ReaderHelper(path_bin,1);
        ReaderHelper(path_item,0);
    }
}
