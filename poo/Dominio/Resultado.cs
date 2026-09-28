namespace LabirintoPoo.Dominio;

// Os três desfechos possíveis herdam daqui e compartilham a linha "Resultado: "
public abstract class Resultado
{
    public override string ToString()
    {
        return "Resultado: " + Descricao();
    }

    protected abstract string Descricao();
}