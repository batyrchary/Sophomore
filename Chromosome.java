import java.util.ArrayList;

public class Chromosome
{
    public static class Fitness
    {
        public float flatency=0;
        public float fbin=0;
        public float fhybrid=0;



        public  Fitness(float fbin, float flatency, float fhybrid)
        {
            this.fbin=fbin;
            this.flatency=flatency;
            this.fhybrid=fhybrid;
        }
    }

    public ArrayList<Gene> chromosome=new ArrayList<>();
    public Fitness hfitnes=new Fitness(0,0,0);
    public int bins=0;
    public float latency=0;

    public int rank=-1;
    public int np=0;
    public float distance=0;
    ArrayList<Chromosome> Sp=new ArrayList<>();

    public ArrayList<ResourceAllocationGA.assignmentPair> assignments=new ArrayList<>();

    public Chromosome(){}
    public Chromosome(Chromosome c)
    {
        for(int i=0; i<c.size();i++)
        {
            Gene g=new Gene(c.get(i));
            this.chromosome.add(g);
            this.hfitnes=new Fitness(c.hfitnes.fbin, c.hfitnes.flatency, c.hfitnes.fhybrid);
            this.bins=c.bins;
            this.latency=c.latency;

            this.rank=c.rank;
            this.np=c.np;
            this.distance=c.distance;
            this.Sp=c.Sp;
        }
        this.assignments.clear();
        for(int j=0; j<c.assignments.size(); j++)
        {
            this.assignments.add(new ResourceAllocationGA.assignmentPair(c.assignments.get(j).tID,c.assignments.get(j).mID));
        }
    }

    public void add(Gene g)
    {
        chromosome.add(g);
    }
    public int size()
    {
        return chromosome.size();
    }
    public Gene get(int i)
    {
        return chromosome.get(i);
    }

    public float getFitness1()
    {
        return hfitnes.fbin;
    }
    public float getFitness2()
    {
        return hfitnes.flatency;
    }
    public float getFitness3()
    {
        return hfitnes.fhybrid;
    }
    public float getFitness(String type)
    {
        if(type.equals("bin"))
            return getFitness1();
        else if(type.equals("latency"))
            return getFitness2();
        else
            return getFitness3();
    }
}