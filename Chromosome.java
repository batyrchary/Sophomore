import java.util.ArrayList;

public class Chromosome
{
    public ArrayList<Gene> chromosome=new ArrayList<>();
    public float fitness=0;
    public int bins=0;

    public ArrayList<ResourceAllocationGA.assignmentPair> assignments=new ArrayList<>();

    public Chromosome(){}
    public Chromosome(Chromosome c)
    {
        for(int i=0; i<c.size();i++)
        {
            Gene g=new Gene(c.get(i));
            this.chromosome.add(g);
            this.fitness=c.fitness;
            this.bins=c.bins;
        }
        this.assignments.clear();
        for(int j=0; j<c.assignments.size(); j++)
        {
            this.assignments.add(new ResourceAllocationGA.assignmentPair(c.assignments.get(j).tID,c.assignments.get(j).mID));
        }
    }

    public float getFitness() {
        return fitness;
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
}