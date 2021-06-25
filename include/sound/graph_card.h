/* SPDX-License-Identifier: GPL-2.0
 *
 * ASoC audio graph card support
 *
 */

#ifndef __GRAPH_CARD_H
#define __GRAPH_CARD_H

#include <sound/simple_card_utils.h>

<<<<<<< HEAD
int audio_graph_card_probe(struct snd_soc_card *card);

int audio_graph_parse_of(struct asoc_simple_priv *priv, struct device *dev);

int audio_graph_remove(struct platform_device *pdev);
=======
int graph_card_probe(struct snd_soc_card *card);

int graph_parse_of(struct asoc_simple_priv *priv, struct device *dev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* __GRAPH_CARD_H */
