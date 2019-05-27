import java.util.ArrayList;
import java.util.Random;

public class IndividualSelection
{
    public static float RandomPoint(Population generation)
    {
        float allfitness=0;


        for(int i=0; i<generation.size();i++)
        {
            allfitness=allfitness+generation.get(i).fitness;
        }

        Random r = new Random();
        float random=0+r.nextFloat()*(allfitness-0);

        //System.out.println("allFitness="+allfitness+"\trandom="+random);

        return random;
    }


    public static Chromosome RouletteWheel(Population generation)
    {
        float randomInt=RandomPoint(generation);

        float wheel=0;
        for(int i=0; i<generation.size();i++)
        {
            wheel=wheel+generation.get(i).fitness;

            if(randomInt<wheel)
                return generation.get(i);
        }
        System.out.println("Problem in individual selection1");
        return generation.get(generation.size()-1);
    }


    public static Chromosome Tournament(Population generation)
    {
        Random r = new Random();
        int random1=r.nextInt(generation.size()-1);
        int random2=r.nextInt(generation.size()-1);

        if(random1==random2)
            return generation.get(random1);

        if(generation.get(random1).fitness > generation.get(random2).fitness)
            return generation.get(random1);
        else
            return generation.get(random2);
    }
}