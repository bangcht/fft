omp_set_num_threads(4);
				#pragma omp parallel private(id)
					{
					#pragma omp for schedule(static) nowait
						for (id = bf_id; id < bf_id + step; id++){
							temp = data[id];
							data[id] = temp + data[id + step];
							data[id + step] = (temp - data[id + step]) * w[w_id];
							w_id += w_step;
						}
					}