#include "../../includes/minishell.h"

char **envp_reorder(char **envp)
{
	int	size;
	int	inner;
	int out;

	size = envp_len(envp);
	inner = 0;
	while ()
	// Fazer a ordenação do array por order alfabética
	// Precisa ser impresso igual ao 'export' sem flags
	// Isso é só a primeira parte do export
	// Quando se imprime só com export ele imprime todas as variáveis
	// ENV e as variáveis EXPORT
	// Quando se usa ENV, as variáveis que são só EXPORT não são impressas
	// Variáveis que são EXPORTADAS sem valor e sem '=', são apenas EXPORT
	// Estas variáveis se tornam ENV quando atribuem algum tipo de valor a elas
	// E continuam ENV ainda que tenham seus valores apagados
	// Se forem exportadas com '=' são ENV

}

int	ft_export(t_envp *envp, char **cmd)
{
	char	**table;
	int		size;


	if (!cmd)
		return (1);
	if (!cmd[1])
	{
		table = envp_rebuilt(envp, ENV | EXPORT);

	}
}
