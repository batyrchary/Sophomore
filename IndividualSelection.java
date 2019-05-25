import java.util.ArrayList;
import java.util.Random;

public class IndividualSelection {




    public static float allFitness(Population generation, int maximumMach, String type, boolean ratioVarmi)
    {
        float allfitness=0;

        float allfitnessb=0;
        float allfitnessl=0;
        float allfitnessh=0;

        for(int i=0; i<generation.size();i++)
        {
            allfitnessb=allfitness+generation.get(i).hfitnes.fbin;
            allfitnessl=allfitness+generation.get(i).hfitnes.flatency;
            allfitnessh=allfitness+generation.get(i).hfitnes.fhybrid;
        }

        float rat=allfitnessl/allfitnessb;

        if(type.equals("bin"))
            allfitness=allfitnessb;
        if(type.equals("latency"))
            allfitness=allfitnessl;
        if(type.equals("hybrid"))
            allfitness=allfitnessl*rat+allfitnessb;



        Random r = new Random();
        float random=0+r.nextFloat()*(allfitness-0);


        if (ratioVarmi==false)
            return random;
        else
            return rat;
    }


    public static Chromosome RouletteWheel(Population generation, int maximumMach, String type)
    {
        float ratioLtoB=allFitness(generation, maximumMach, type, true);
        float randomInt=allFitness(generation, maximumMach, type, false);

        float allfitnessb=0;
        float allfitnessl=0;
        float allfitnessh=0;

        float wheel=0;
        for(int i=0; i<generation.size();i++)
        {

            allfitnessb=generation.get(i).hfitnes.fbin;
            allfitnessl=generation.get(i).hfitnes.flatency;
            allfitnessh=generation.get(i).hfitnes.fhybrid;


            if(type.equals("bin"))
                wheel=wheel+allfitnessb;
            if(type.equals("latency"))
                wheel=wheel+allfitnessl;
            if(type.equals("hybrid"))
                wheel=wheel+allfitnessl*ratioLtoB+allfitnessb;

            if(randomInt<wheel)
                return generation.get(i);
        }
        System.out.println("Problem in individual selection1");
        return generation.get(generation.size()-1);
    }


    public static Chromosome Tournament(Population generation, String type)
    {
        Random r = new Random();
        int random1=r.nextInt(generation.size()-1);
        int random2=r.nextInt(generation.size()-1);

        if(random1==random2)
            return generation.get(random1);

        if(type.equals("bin"))
        {
            if(generation.get(random1).hfitnes.fbin > generation.get(random2).hfitnes.fbin)
                return generation.get(random1);
            else
                return generation.get(random2);
        }
        else
        {
            if(generation.get(random1).hfitnes.flatency > generation.get(random2).hfitnes.flatency)
                return generation.get(random1);
            else
                return generation.get(random2);
        }
    }
}