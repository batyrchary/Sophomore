import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public  class Population
{

    public ArrayList<Chromosome> chromosomes = new ArrayList<>();

    public Population() { this.chromosomes=new ArrayList<>(); }
    public Population(ArrayList<Chromosome> chromosomes)
    {
        for(int i=0; i<chromosomes.size(); i++)
        {
            Chromosome c = new Chromosome (chromosomes.get(i));
            this.add(c);
        }
    }

    public void add(Chromosome c) {
        chromosomes.add(c);
    }

    public int size() {
        return this.chromosomes.size();
    }
    public int indexOf(Chromosome c) {
        return this.chromosomes.indexOf(c);
    }
    public void remove(int index) {
         this.chromosomes.remove(index);
    }

    public Chromosome get(int i) {
        return chromosomes.get(i);
    }


    public Population addTwoPopulation(Population p1, Population p2)
    {
        Population ret = new Population();

        for (int i = 0; i < p1.size(); i++)
        {
            Chromosome c=new Chromosome(p1.get(i));
            ret.add(c);
        }

        for (int i = 0; i < p2.size(); i++)
        {
            Chromosome c=new Chromosome(p2.get(i));
            ret.add(c);
        }
        return ret;
    }

    public Population sortByFitness(Population p1, String type) {


        ArrayList<Chromosome> ret = new ArrayList<>();

        for(int i=0; i<p1.chromosomes.size(); i++)
        {
            Chromosome c=new Chromosome(p1.get(i));
            ret.add(c);
        }

        Collections.sort(ret, new Comparator<Chromosome>()
        {
            @Override
            public int compare(Chromosome p1, Chromosome p2) {
                float p1f=0;
                float p2f=0;
                if(type.equals("bin"))
                {
                    p1f=p1.hfitnes.fbin;
                    p2f=p2.hfitnes.fbin;
                }
                else if(type.equals("latency"))
                {
                    p1f=p1.hfitnes.flatency;
                    p2f=p2.hfitnes.flatency;
                }
                else
                {
                    p1f=p1.hfitnes.fhybrid;
                    p2f=p2.hfitnes.fhybrid;
                }
                if(p1f>p2f)
                {
                    return 1;
                }
                else if(p1f<p2f)
                {
                    return -1;
                }
                else
                {
                    return 0; // Ascending
                }
            }
        });

        if(type.equals("bin"))
            ret.sort(Comparator.comparingDouble(Chromosome::getFitness1)); //smallest to largest
        else if(type.equals("latency"))
            ret.sort(Comparator.comparingDouble(Chromosome::getFitness2)); //smallest to largest
        else if(type.equals("hybrid"))
            ret.sort(Comparator.comparingDouble(Chromosome::getFitness3)); //smallest to largest

        Collections.reverse(ret);
        return new Population(ret);
    }
}